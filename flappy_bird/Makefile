CC      = gcc
LIB_DIR = ../lib
CFLAGS = -Wall -Wextra -MMD -MP -I$(LIB_DIR)
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

# Windows cross-compile settings
WIN_CC     = x86_64-w64-mingw32-gcc
WIN_SDL    = $(HOME)/sdl2-win/x86_64-w64-mingw32
WIN_SDL_IMG= $(HOME)/sdl2_image-win/x86_64-w64-mingw32
WIN_MIX    = $(HOME)/sdl2_mixer-win/x86_64-w64-mingw32
WIN_TTF    = $(HOME)/sdl2_ttf-win/x86_64-w64-mingw32
WIN_CFLAGS = -Wall -Wextra -MMD -MP -I$(LIB_DIR) -DSDL_MAIN_HANDLED \
             -I$(WIN_SDL)/include -I$(WIN_SDL)/include/SDL2 \
             -I$(WIN_SDL_IMG)/include -I$(WIN_SDL_IMG)/include/SDL2 \
             -I$(WIN_MIX)/include -I$(WIN_MIX)/include/SDL2 \
             -I$(WIN_TTF)/include -I$(WIN_TTF)/include/SDL2
WIN_LDFLAGS= -L$(WIN_SDL)/lib -L$(WIN_SDL_IMG)/lib -L$(WIN_MIX)/lib -L$(WIN_TTF)/lib \
             -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm -mwindows

SRC_SRC  = $(wildcard src/*.c)
SRC_LIB  = $(wildcard $(LIB_DIR)/*.c)

OBJ      = $(patsubst src/%.c, objects/%.o, $(SRC_SRC)) \
           $(patsubst $(LIB_DIR)/%.c, objects/lib_%.o, $(SRC_LIB))
WIN_OBJ  = $(patsubst src/%.c, objects/win_%.o, $(SRC_SRC)) \
           $(patsubst $(LIB_DIR)/%.c, objects/win_lib_%.o, $(SRC_LIB))

BUILD_DIR  = builds
TARGET     = $(BUILD_DIR)/linux/game
WIN_TARGET = $(BUILD_DIR)/windows/game.exe

$(TARGET): $(OBJ) | $(BUILD_DIR)/linux
	$(CC) $^ -o $@ $(LDFLAGS)

$(WIN_TARGET): $(WIN_OBJ) | $(BUILD_DIR)/windows
	$(WIN_CC) $^ -o $@ $(WIN_LDFLAGS)

objects/%.o: src/%.c | objects
	$(CC) $(CFLAGS) -c $< -o $@

objects/lib_%.o: $(LIB_DIR)/%.c | objects
	$(CC) $(CFLAGS) -c $< -o $@

objects/win_%.o: src/%.c | objects
	$(WIN_CC) $(WIN_CFLAGS) -c $< -o $@

objects/win_lib_%.o: $(LIB_DIR)/%.c | objects
	$(WIN_CC) $(WIN_CFLAGS) -c $< -o $@

objects:
	mkdir -p objects

$(BUILD_DIR)/linux $(BUILD_DIR)/windows:
	mkdir -p $@

-include $(OBJ:.o=.d)
-include $(WIN_OBJ:.o=.d)

all: linux windows

linux: $(TARGET)
	cp -r res $(BUILD_DIR)/linux/

# Package a self-contained Windows folder: exe + runtime DLLs + resources,
# so game.exe finds res/ relative to its own working directory.
windows: $(WIN_TARGET)
	cp -r res $(BUILD_DIR)/windows/
	cp $(WIN_SDL)/bin/SDL2.dll $(WIN_SDL_IMG)/bin/SDL2_image.dll $(WIN_MIX)/bin/SDL2_mixer.dll $(WIN_TTF)/bin/SDL2_ttf.dll $(BUILD_DIR)/windows/

run: linux
	./$(TARGET)

clean:
	rm -rf objects $(BUILD_DIR)/linux $(BUILD_DIR)/windows

.PHONY: all linux windows run clean