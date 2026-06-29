# Games

A small collection of games written in C with SDL2, sharing a common library.

## Layout

```
Games/
├── lib/            shared game library (vector math, entity/texture helpers)
└── flappy_bird/    Flappy Bird clone built on lib/
    ├── src/        game code
    ├── res/        textures
    └── Makefile    build is run from here
```

## Dependencies

- `gcc`, `make`
- `SDL2` and `SDL2_image` (development headers)

On Debian/Ubuntu: `sudo apt install build-essential libsdl2-dev libsdl2-image-dev`

## Building & running (Linux)

```sh
cd flappy_bird
make run        # builds builds/linux/game and runs it
```

`make` (or `make linux`) just builds; the binary lands in `flappy_bird/builds/linux/`.

## Windows build (cross-compile)

Requires the MinGW-w64 toolchain and Windows SDL2 / SDL2_image packages
(paths configured at the top of `flappy_bird/Makefile`).

```sh
cd flappy_bird
make windows    # produces a self-contained builds/windows/ (game.exe + DLLs + res/)
```

## Controls

- **Space** / **Left click** — flap
- **Esc** — quit
