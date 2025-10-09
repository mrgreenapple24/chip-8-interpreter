#include <stdio.h>

unsigned short opcode; // 35 opcodes 2 bytes long
unsigned char memory[4096]; // 4k memory

unsigned char V[16]; // 16 8-bit registers
unsigned short I; // stores memory addresses
unsigned short pc; // program counter -> stores currently executing address

unsigned char gfx[64*32];
// graphics of chip-8 are black and white and the screen has a total of 2048 pixels (64 * 32)
unsigned char delay_timer;
unsigned char sound_timer;

unsigned short stack[16];
unsigned short sp;

unsigned char key[16];
// hex based keypad, array stores current state of the key
