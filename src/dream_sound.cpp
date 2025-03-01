#include<dream_sound.h>
#include<dream_variables.h>
#include<SDL.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE 28000

void play_beep(float frequency, int duration) {
    SDL_LockAudio();
    sound.frequency = frequency;
    sound.duration_samples = (SAMPLE_RATE * duration) / 1000;
    sound.sample_count = 0;
    sound.active = 1;

    sound.end_time = SDL_GetTicks() + duration;
    SDL_UnlockAudio();
}

