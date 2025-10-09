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

void emulateCycle() {
    // fetch opcode
    opcode = memory[pc] << 8 | memory[pc+1];
    // decode opcode
    __uint8_t x = opcode & 0x0F00;
    __uint8_t y = opcode & 0x00F0;
    __uint8_t kk = opcode & 0x00FF;
    __uint16_t nnn = opcode & 0x0FFF;

    switch(opcode & 0xF000) {
        case 0x0000: {
            switch(kk) {
                case 0x00E0: {
                    // clear display
                }

                case 0x00EE: { // return from subroutine
                    pc = stack[sp];
                    sp--;
                    break;
                }

                default: {
                    printf("Unknown opcode 0x%X\n", opcode);
                }
            }
            break;
        }


        case 0x1000: { // jump to location
            pc = nnn;
            break;
        }


        case 0x2000: { // call subroutine at location
            stack[sp] = pc;
            sp++;
            pc = nnn;
            break;
        }

        case 0x3000: { // skip next instruction if Vx == kk
            if (V[x] == (kk)) {
                pc += 2;
            }

            pc += 2;
            break;
        }

        case 0x4000: { // skip next instruction if Vx != kk
            if (V[x] != (kk)) {
                pc += 2;
            }

            pc += 2;
            break;
        }

        case 0x5000: { // skip next instruction if Vx == Vy
            if (V[x] == V[y]) {
                pc += 2;
            }

            pc += 2;
            break;
        }

        case 0x6000: { // Set Vx = kk
            V[x] = kk;
            pc += 2;

            break;
        }

        case 0x7000: { // Set Vx = Vx + kk
            V[x] = V[x] + (kk);
            pc += 2;

            break;
        }

        case 0x8000: { // Set Vx = Vy
            switch (opcode & 0x000F) {
                case 0x0000: { // set Vx = Vy
                    V[x] = V[y];
                    pc += 2;
                    break;
                }

                case 0x0001: { // set Vx = Vx OR Vy
                    V[x] = V[x] | V[y];
                    pc += 2;
                    break;
                }

                case 0x0002: { // set Vx = Vx AND Vy
                    V[x] = V[x] & V[y];
                    pc += 2;
                    break;
                }

                case 0x0003: { // set Vx = Vx XOR Vy
                    V[x] = V[x] ^ V[y];
                    pc += 2;
                    break;
                }

                case 0x0004: { // set Vx = Vx + Vy, set VF = carry
                    V[0xF] = (V[x] > 0xFF - V[y] ? 1 : 0);
                    V[x] = (V[x] + V[y]) & 0xFF;
                    pc += 2;
                    break;
                }

                case 0x0005: { // set Vx = Vx - Vy, set VF = NOT borrow
                    V[0xF] = (V[x] > V[y] ? 1 : 0);
                    V[x] = V[x] - V[y];
                    pc += 2;
                    break;
                }

                case 0x0006: { // set Vx = Vx SHR 1
                    V[0xF] = (V[x] & 0x01 ? 1 : 0);
                    V[x] /= 2;

                    pc += 2;
                    break;
                }

                case 0x0007: { // set Vx = Vy-Vx, set VF = NOT borrow
                    V[0xF] = (V[y] > V[x] ? 1 : 0);
                    V[x] = V[y] - V[x];

                    pc += 2;
                    break;
                }

                case 0x000E: { // Set Vx =  Vx SHL 1
                    V[0xF] = (V[x] & 0x80 ? 1 : 0);
                    V[x] *= 2;

                    pc += 2;
                    break;
                }

                default: {
                    printf("Wrong opcode: 0x%X\n", opcode);
                }
            }
            break;
        }

        case 0x9000: { // skip next instruction if Vx != Vy
            if (V[x] != V[y]) {
                pc += 2;
            }

            pc += 2;
            break;
        }

        case 0xA000: { // Set I = nnn
            I = opcode & 0x0FFF;
            pc += 2;
            break;
        }

        case 0xB000: { // jump to location nnn + V0
            pc = nnn + V[0];
            break;
        }

        case 0xC000: {
            // random byte and kk
        }

        case 0xD000: {
            // Display n-byte sprite starting at memroy location I at (Vx, Vy), set VF = collision
        }

        case 0xE000: {
            switch (kk) {
                case 0x009E: {
                    // skip next instruction if key with value Vx is pressed
                }

                case 0x00A1: {
                    // opposite of first case
                }

                default: {
                    printf("invalid opcode: 0x%X\n", opcode);
                }
            }
        }

        case 0xF000: {
            switch(kk) {
                case 0x0007: {
                    // Set Vx = delay timer value
                }

                case 0x000A: {
                    // Wait for a key press, store the value of the key in Vx
                }

                case 0x0015: {
                    // set delay timer = Vx
                }

                case 0x0029: {
                    // set I =  location of sprite for digit Vx
                }

                case 0x0033: {
                    // store bcd representation of Vx in memory locations
                }

                case 0x0055: {
                    // store registers V0 through Vx in memory starting at location I
                }

                case 0x0065: {
                    // read registers V0 through Vx from memory starting at location I
                }
            }
        }

        default:
            printf("Unknown Opcode: 0x%X\n", opcode);
    }
    // update timers
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