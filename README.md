# Games

> **Version 0.5** — actively developed. The game is playable and the shared library is functional, with several enhancements planned across three phases (see roadmap below).

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

---

## Roadmap

```
 v0.5          Phase 1        Phase 2        Phase 3
  |                |              |              |
  ●────────────────○──────────────○──────────────○
  |                |              |              |
Done           Audio          Font           Sprite
               Support        Support        Support
               + Pong?

[████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░]  v0.5 / 4 milestones
```

### Current — v0.5
- Flappy Bird (playable, with collision, gravity and pipes)
- Shared `lib/` with vector math, entity/texture management

### Phase 1 — Audio Support
- Add SDL2_mixer to `lib/`
- Background music and sound effects for Flappy Bird
- Possibly start **Pong**

### Phase 2 — Font Support
- Add SDL2_ttf to `lib/`
- Score display, menus, game-over screen

### Phase 3 — Sprite Support
- Rework texture handling in `lib/` (currently entity owns a single static texture)
- Sprite sheets, animation frames, multiple textures per entity
