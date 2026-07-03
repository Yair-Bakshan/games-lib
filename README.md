# Games

> **Version 0.9** — actively developed. Audio (Phase 1), font/score display (Phase 2), and sprite animation (Phase 3) are all done. Next up: a second game (**Pong**). See the roadmap below.

A small collection of games written in C with SDL2, sharing a common library.

## Layout

```
Games/
├── lib/            shared game library (vector math, entity, sprite, audio, font)
└── flappy_bird/    Flappy Bird clone built on lib/
    ├── src/        game code
    ├── res/        textures, sounds, music, font
    └── Makefile    build is run from here
```

## Dependencies

- `gcc`, `make`
- `SDL2`, `SDL2_image`, `SDL2_mixer`, `SDL2_ttf` (development headers)

On Debian/Ubuntu:
```sh
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

## Building & running (Linux)

```sh
cd flappy_bird
make run        # builds builds/linux/game and runs it
```

`make` (or `make linux`) just builds; the binary lands in `flappy_bird/builds/linux/`.

## Windows build (cross-compile)

Requires the MinGW-w64 toolchain and the Windows SDL2, SDL2_image, SDL2_mixer
and SDL2_ttf dev packages (paths configured at the top of `flappy_bird/Makefile`).

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
 v0.5          Phase 1        Phase 2        Phase 3        Next
  |                |              |              |            |
  ●────────────────●──────────────●──────────────●───────────○
  |                |              |              |            |
Done            Audio           Font          Sprite        Game Jam
               Support        Support       Animation     (2nd game)
              (done)          (done)         (done)

[██████████████████████████████████████████████]  4 / 4 milestones
```

### v0.5 — Foundation ✅
- Flappy Bird (playable, with collision, gravity and pipes)
- Shared `lib/` with vector math, entity/texture management

### Phase 1 — Audio Support ✅
- Added SDL2_mixer to `lib/` (`audio.h` — `Sound` / `Music`)
- Background music and sound effects (flap, score) for Flappy Bird

### Phase 2 — Font Support ✅
- Added SDL2_ttf to `lib/` (`font.h` — `Font`, `draw_text`)
- Live score display

### Phase 3 — Sprite Animation ✅
- Added `sprite.h` to `lib/` (`Sprite` — multi-frame textures with timed animation)
- `Entity` now references a `Sprite` instead of owning a raw texture; ownership is explicit in the game
- Animated 3-frame flappy bird

### Next — Game Jam
- I will find a game jam and start a second game on the shared `lib/` to prove out reuse
