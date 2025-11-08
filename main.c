#include "defs.h"

void initialize() {
    int i;
    // Initialize registers and memory once
    pc = 0x200; // pc starts at this address
    opcode = 0; // reset current opcode
    I = 0; // reset index register
    sp = 0; // reset stack pointer
    
    memset(gfx, 0, sizeof(uint8_t) * 64 * 32);
    // clear display
    memset(stack, 0, sizeof(uint16_t) * 16);
    // clear stack
    memset(V, 0, sizeof(uint8_t) * 16):
    // clear registers V0-VF
    memset(memory, 0, sizeof(uint8_t) * 4096);
    // clear memory
    memset(key, 0, sizeof(uint8_t) * 16);


    // load fontset
    for (int i = 0; i < 80; i++) {
        memory[i] =  chip8_fontset[i];
    }

    // reset timers
    delay_timer = 0;
    sound_timer = 0;
    srand(time(NULL));
}



void loadGame(char *game) {
    FILE *fgame;

    fgame = fopen(game, "rb");

    if (fgame == NULL) {
      fprintf(stderr, "Unable to open game: %s\n", game);
      exit(42);
    }

    fread(&memory[0x200], 1, MAX_GAME_SIZE, fgame);
    
    fclose(fgame);
}

int main(int argc, char **argv) {
    // set up render system and register input callbacks
    setupGraphics();
    setupInput();

    // initialize the chip8 system and load the game into the memory
    initialize();
    loadGame("pong");

    // emulation loop
    for (;;) {
        // emulate one cycle
        emulateCycle();

        // if the draw flag is set, update the screen
        if (drawFlag) {
            drawGraphics();
        }

        // store key press state
        setKeys();
    }
}
