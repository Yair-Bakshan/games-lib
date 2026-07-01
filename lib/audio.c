#include "audio.h"

// Init / quit
bool audio_init(void) {
    /* Args: frequency (44100 = CD quality), format,
       channels (2 = stereo), chunk size */
    return Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0;
}

void audio_quit(void) {
    Mix_CloseAudio();
}

// Sound effects
bool load_sound(Sound *s, const char *file) {
    s->chunk = Mix_LoadWAV(file);
    return s->chunk != NULL;
}
void play_sound(Sound *s) {
    if(!s->chunk) return;
    Mix_PlayChannel(-1, s->chunk, 0); // -1 means it picks automaticly channel
}
void free_sound(Sound *s) {
    Mix_FreeChunk(s->chunk);
    s->chunk = NULL;
}

// Music
bool load_music(Music *m, const char *file) {
    m->track = Mix_LoadMUS(file);
    return m->track != NULL;
}
void play_music(Music *m) {
    if (!m->track) return;
    Mix_PlayMusic(m->track, -1); // -1 = loop forever
}
void stop_music(void) {
    Mix_HaltMusic();
}
void free_music(Music *m) {
    Mix_FreeMusic(m->track);
    m->track = NULL;
}