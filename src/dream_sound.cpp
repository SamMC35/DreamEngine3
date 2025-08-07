#include<dream_sound.h>
#include<dream_variables.h>
#include<SDL.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE 28000
#define MAX_CHANNELS 4;

void playBeep(int channel, float frequency, int duration) {
    if (channel < 0 || channel >= 4) return;

    SDL_LockAudio();
    channels[channel].frequency = frequency;
    channels[channel].duration_samples = (SAMPLE_RATE * duration) / 1000;
    channels[channel].sample_count = 0;
    channels[channel].end_time = SDL_GetTicks() + duration;
    channels[channel].active = 1;
    SDL_UnlockAudio();
}

