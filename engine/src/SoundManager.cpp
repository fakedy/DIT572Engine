#include <Engine/SoundManager.h>


static SDL_AudioStream* stream = NULL;
static Uint8* wav_data = NULL;
static Uint32 wav_data_len = 0;


namespace Engine {


	SoundManager::SoundManager() {

	}

	void SoundManager::PlaySound() {


        
            SDL_AudioSpec spec;
            char* wav_path = NULL;


            /* Load the .wav file from wherever the app is being run from. */
            SDL_asprintf(&wav_path, "%test.wav", SDL_GetBasePath());  /* allocate a string of the full file path */
            if (!SDL_LoadWAV(wav_path, &spec, &wav_data, &wav_data_len)) {
                SDL_Log("Couldn't load .wav file: %s", SDL_GetError());
            }

            SDL_free(wav_path);  /* done with this string. */

            /* Create our audio stream in the same format as the .wav file. It'll convert to what the audio hardware wants. */
            stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
            if (!stream) {
                SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
            }

            /* SDL_OpenAudioDeviceStream starts the device paused. You have to tell it to start! */
            SDL_ResumeAudioStreamDevice(stream);

            /* see if we need to feed the audio stream more data yet.
               We're being lazy here, but if there's less than the entire wav file left to play,
               just shove a whole copy of it into the queue, so we always have _tons_ of
               data queued for playback. */
            if (SDL_GetAudioStreamQueued(stream) < (int)wav_data_len) {
                /* feed more data to the stream. It will queue at the end, and trickle out as the hardware needs more data. */
                SDL_PutAudioStreamData(stream, wav_data, wav_data_len);
            }



        }

      

        void SoundManager::StopSound()
        {
            SDL_free(wav_data);  /* strictly speaking, this isn't necessary because the process is ending, but it's good policy. */
            /* SDL will clean up the window/renderer for us. */
        }
	}


