# games-lib

A small game library for C, built on top of SDL2. It provides vector math, entities, sprite animation, audio and text rendering. A Flappy Bird clone shows how to use it.

**Status:** version 0.9. Audio, font rendering and sprite animation are done. Next: a second game on the same library.

## Library

The library is in `lib/`. Each module is one header and one source file.

| Module | What it provides |
|---|---|
| `vector.h` | `Vector2` type with `add_vector2`, `sub_vector2` and `get_center` |
| `entity.h` | `Entity` (sprite, position, scale, angle), drawing, and collision checks between two entities |
| `sprite.h` | Multi-frame sprites with timed animation |
| `audio.h` | Sound effects and looping music (SDL2_mixer) |
| `font.h` | Loading TrueType fonts and drawing text (SDL2_ttf) |

### Example

```c
sprite_init();                                  // initialize SDL2_image

Sprite bird = {0};
load_sprite(&bird, 0.125, ren,                  // 0.125 s per frame
            "res/Flappy1.png", "res/Flappy2.png", "res/Flappy3.png",
            NULL);                              // the list of files ends with NULL

Entity player = { .sprite = &bird, .pos = {400, 400}, .scale = {75, 75} };

draw_entity(&player, dt, ren);                  // advances the animation and draws
```

`pos` is the center of the entity. Collision checks use axis-aligned boxes and ignore rotation.

## Flappy Bird

`flappy_bird/` is a complete game built on the library.

| Input | Action |
|---|---|
| Space or left click | Flap |
| Esc | Quit |

The game closes when you hit a pipe or leave the screen.

## Project Layout

```
games-lib/
├── lib/            shared library (vector, entity, sprite, audio, font)
└── flappy_bird/    Flappy Bird clone built on lib/
    ├── src/        game code
    ├── res/        textures, sounds, music, font
    └── Makefile    run builds from this folder
```

## Building

**Dependencies**

- `gcc` and `make`
- Development headers for `SDL2`, `SDL2_image`, `SDL2_mixer` and `SDL2_ttf`

On Debian or Ubuntu:

```bash
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

**Linux**

```bash
cd flappy_bird
make run        # build and run
make linux      # build and copy res/ to builds/linux/
```

**Windows (cross-compile from Linux)**

You need the MinGW-w64 toolchain and the Windows development packages of SDL2, SDL2_image, SDL2_mixer and SDL2_ttf. The Makefile expects them in `~/sdl2-win`, `~/sdl2_image-win`, `~/sdl2_mixer-win` and `~/sdl2_ttf-win`. You can change these paths at the top of `flappy_bird/Makefile`.

```bash
cd flappy_bird
make windows    # creates builds/windows/ with game.exe, DLLs and res/
```

## Roadmap

- [x] Foundation: Flappy Bird, vector math, entities and textures
- [x] Audio: music and sound effects with SDL2_mixer
- [x] Font support: score display with SDL2_ttf
- [x] Sprite animation: multi-frame sprites with timed animation
- [ ] Second game built on the same library

## License

Released under the [MIT License](LICENSE).
