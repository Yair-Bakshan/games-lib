#ifndef LIB_AUDIO_H
#define LIB_AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

typedef struct {
    Mix_Chunk *chunk;
} Sound;

typedef struct {
    Mix_Music *track;
} Music;

// Init / quit
bool audio_init(void);
void audio_quit(void);

// Sound effects
bool load_sound(Sound *s, const char *file);
void play_sound(Sound *s);
void free_sound(Sound *s);

// Music
bool load_music(Music *m, const char *file);
void play_music(Music *m);   // loops forever
void stop_music(void);
void free_music(Music *m);

#endif