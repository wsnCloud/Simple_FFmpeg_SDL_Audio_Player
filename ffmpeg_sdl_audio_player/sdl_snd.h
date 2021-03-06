/**
 * Copyright 2016 cocafe <cocafehj@gmail.com> All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "stdafx.h"

#include <sdl\SDL.h>
#include <sdl\SDL_audio.h>

#define SDL_FEATURES				(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)

/* Volume over maximum means gain */
#define AUDIO_VOLUME_MIN			(0)
#define AUDIO_VOLUME_MAX			(SDL_MIX_MAXVOLUME)
#define AUDIO_VOLUME_OVER			(AUDIO_VOLUME_MAX * 2)
#define AUDIO_VOLUME_DEFAULT		(AUDIO_VOLUME_MAX)

typedef struct SDLPlaybackBuffer {
	uint8_t							*chunk;
	int32_t							chunk_size;
	int32_t							nb_samples;
	int32_t							pos;
	int32_t							refill_pending;
} SDLPlaybackBuffer;

typedef struct SDLPlaybackData {
	SDLPlaybackBuffer				*buf;

	int32_t							volume;
	HANDLE							hSemSDLPlaybackPending;
} SDLPlaybackData;

typedef struct SDLAudioData {
	SDL_AudioSpec					*spec;
	SDL_AudioSpec					*spec_ret;
	SDLPlaybackData					*playback_data;
} SDLAudioData;

SDLAudioData *sdl_audio_data_alloc(void);
void sdl_audio_data_free(SDLAudioData **sad);

int sdl_audio_data_init(
	SDLAudioData *sad,
	uint16_t sdl_sample_rate,
	SDL_AudioFormat sdl_sample_fmt,
	uint16_t sdl_nb_samples,
	uint8_t sdl_channels);
void sdl_audio_data_exit(SDLAudioData *sad);

int sdl_audio_playback_init(
	SDLPlaybackData *pbdata,
	int32_t volume_def);

int sdl_audio_playback_refill(
	SDLPlaybackData *pbdata,
	uint8_t *chunk_ref,
	int32_t chunk_size,
	int32_t nb_samples);

int sdl_audio_playback_pending(SDLPlaybackData *pbdata);