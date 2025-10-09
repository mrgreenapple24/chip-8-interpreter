#include "defs.h"

void initialize() {
    // Initialize registers and memory once
    pc = 0x200; // pc starts at this address
    opcode = 0; // reset current opcode
    I = 0; // reset index register
    sp = 0; // reset stack pointer

    // clear display
    // clear stack
    // clear registers V0-VF
    // clear memory


    // load fontset
    for (int i = 0; i < 80; i++) {
        memory[i] =  chip8_fontset[i];
    }

    // reset timers
}



void loadGame() {
    for (int i = 0; i < bufferSize; i++) {
        memory[i+512] = buffer[i];
    }
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