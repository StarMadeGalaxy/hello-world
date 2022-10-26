#include "[ILYUK]chip_eighth.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void IlyukChip8::initialize()
{

	unsigned char chip8_fontset[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	PC = 0x200;			// Program counter start aat 0x200
	opcode = 0;			// Reset current opcode
	I = 0;				// Reset index register
	SP = 0;				// Reset the stack pointer
	delay_timer = 0;	// Reset the delay timer
	sound_timer = 0;	// Reset the delay timer

	for (int i = 0; i < 80; i++)			// Load fontset in the memory
	{
		memory[i] = chip8_fontset[i];
	}

	for (int i = 0; i < (64 * 32); ++i)		// Clear the display
	{
		graphics[i] = 0;
	}

	for (int i = 0; i < 16; ++i)			// Clear stack, keyboard and registers at the same time together
	{
		stack[i] = key[i] = V[i] = 0;
	}
}

void IlyukChip8::IlyukEmulateCycle()
{
	opcode = memory[PC] << 8 | memory[PC + 0x0001];	// Fetch two bytes and merge them into 16-bit opcode with & 

	switch (opcode & 0xF000)						// Estimate the first hex number in opcode
	{
		case 0x0000:
			switch (opcode & 0x000F)				// Estimate the last hex number in opcode
			{
			case 0x0000:							// We have finally figured out the opcode and this is the 0x(0)0E(0) - Clear the screen, in () what exactly we have estimated 
				for (int i = 0; i < (64 * 32); ++i)
				{
					graphics[i] = 0;
					drawFlag = true;	// I assume drawFlag is need for specify clear display or not 
				}
				PC += 2;				// +2 because of memory-array contains 4096 cells byte-long, but opcode is 2-byte long that means one opcode consist of two memory-array cells
				break;

			case 0x000E:				// 0x00EE, returns from a subroutine
				--SP;					// Every program is the sequence of opcodes and when one of the opcodes call a subroutine it increases SP by 1 
				PC = stack[SP];			// When subroutine wants to return something it decreases SP by 1 to tell PC position of the mother routine
				PC += 2;				// and then increases PC to carry out the next opcode
				break;

			default:
				printf("Unknown opcode [0x0000]: 0x%X\n", opcode);
				break;
			}
			break;

		case 0x1000:				// 1NNN: Jumps to address NNN. The interpreter sets the PC to NNN, whereas NNN is a 12-bit value, the lowest 12 bits of the instruction
			PC = opcode & 0x0FFF;	// 0x0FFF = 0000.1111.1111.1111
			break;

		case 0x2000:				// 2NNN: Calls subrotuine at NNN. 
			stack[SP] = PC;			// Store current state of PC in the stack so the program will be able to return where it left with RETURN instruction
			PC = opcode & 0x0FFF;	
			++SP;					// Increase SP to prevent overwrite, for example: is subroutine 1 calls subroutine 2. If we had not done ++SP
			break;					// subroutine 2 would overwrite the return address of subroutine 1, therefore only return address for sub2 would be in the stack

		case 0x3000:				// 3XNN: Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
			if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))		// >> 8 because we need to compare V[X] and NN, not V[X00] and NN
			{
				PC += 4;
			}
			else
			{
				PC += 2;
			}
			break;

		case 0x4000:				// 4XNN: Skips the next instruction if Vx doesn't equal NN (Usually the next instruction is a jump to skip a code block)
			if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
			{
				PC += 4;
			}
			else
			{
				PC += 2;
			}
			break;

		case 0x5000:				// 5XY0: Skips the next instruction if VX doesnt equals VY (Usually the next instruction is a jump to skip a code block)
			if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
			{
				PC += 4;
			}
			else
			{
				PC += 2;
			}
			break;

		case 0x6000:				// 6XNN: Sets VX to NN
			V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
			PC += 2;
			break;

		case 0x7000:				// 7XNN: Adds NN to VX (Carry flag is not changed)
			V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
			PC += 2;
			break;

		case 0x8000:		
			switch (opcode & 0x000F)
			{
				case 0x0000:		// 8XY0: Sets VX to the value of VY
					V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
					PC += 2;
					break;

				case 0x0001:		// 8XY1: Sets VX to (VX OR VY)
					V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
					PC += 2;
					break;

				case 0x0002:		// 8XY2: Sets VX to (VX AND VY)
					V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
					PC += 2;
					break;

				case 0x0003:		// 8XY3: Sets VX to (VX XOR VY)
					V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
					PC += 2;
					break;

				case 0x0004:		// 8XY4 Adds VY to VX. VF is set to 1 when there is a carry, and to 0 when there is not
					if ((V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4]) > 0xFF) 
					{				// If the result is greater than 8 bits(i.e., > 255, ) VF is set to 1, otherwise 0
	
						V[0xF] = 1; 
					}
					else
					{
						V[0xF] = 0;
					}
					PC += 2;
					break;

				case 0x0005:		// 8XY5: VY is subtracted from VX. If Vx > Vy, then VF is set to 1, otherwise 0
					if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4])
					{				
						V[0xF] = 1;
					}
					else
					{
						V[0xF] = 0;
					}
					V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
					PC += 2;
					break;

				case 0x0006:		// 8XY6: Store the least significant bit of VX in VF and then shifts VX to the right by 1
					V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;		
					V[(opcode & 0x0F00) >> 8] >>= 1;
					PC += 2;
					break;
				
				case 0x0007:		//8XY7: Sets VX to VY minus VX. If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
					if (V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8])
					{
						V[0xF] = 1;
					}
					else
					{
						V[0xF] = 1;
					}
					V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
					PC += 2;
					break;
				
				case 0x000E:		// 8XYE: Stores the most significant bit of VX in VF and then shift VX to the left by 1
					V[0xF] = (V[(opcode & 0x0F00) >> 8]) >> 7;		// >> 7 because VX is a 8-bit register, and the most significant bit is the most left bit 
					V[(opcode & 0x0F00) >> 8] <<= 1;
					PC += 2;
					break;

				default:
					printf("Unknown opcode [0x8000]: 0x%X\n", opcode);
					break;
			}
			break;

		case 0x9000:				// 9XY0: Skips the next instruction if VX does not equal to VY
			if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
			{
				PC += 4;
			}
			else
			{
				PC += 2;
			}
			break;
			
		case 0xA000:				// ANNN: Set I to the address NNN
			I = opcode & 0x0FFF;
			PC += 2;
			break;

		case 0xB000:				// BNNN: Jumps to the address NNN plus V0
			PC = (opcode & 0x0FFF) + V[0];
			break;

		case 0xC000:				// CXNN: Set VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN
			srand(time(NULL));
			V[(opcode & 0x0F00) >> 8] = (0xFF & rand()) & (opcode & 0x00FF);		// 0xFF & rand() - need of that is to limit rand(), if not, can cause to overload
			PC += 2;
			break;

		case 0xD000:				// DXYN: Draws a sprite at coordiante (VX, VY) that has a width of 8 pixels and a height of N pixels. 
									// Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesnt change after
									// the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset	
									// when the sprite is drawn, and to 0 if that does not happen.
									// Cowgod's Chip - 8 Technical Reference v1:
									// The interpreter reads n bytes from memory, starting at the address stored in I.
									// These bytes are then displayed as sprites on screen at coordinates(Vx, Vy).
									// Sprites are XORed onto the existing screen.If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. 
									// If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen.
			unsigned char X = V[(opcode & 0x0F00) >> 8];
			unsigned char Y = V[(opcode & 0x00F0) >> 4];
			unsigned char height = opcode & 0x00F;
			unsigned char pixel;

			V[0xF] = 0;		// We dont have a collision at the beginning of the execution of the opcode 
			for (int y_line = 0; y_line < height; ++y_line)
			{
				pixel = memory[I + y_line];		// Starting at the addres stored and I and increment it 
			}

		case 0xE000:
			switch (opcode & 0x000F)
			{
				case 0x000E:		// EX9E: Skips the next instruction if the key stored in VX is pressed
					if (key[V[(opcode & 0x0F00) >> 8]] != 0)
					{
						PC += 4;
					}
					else
					{
						PC += 2;
					}
					break;

				case 0x0001:		// EXA1: Skips the next insruction if the key stored in VX in not pressed
					if (key[V[(opcode & 0x0F00) >> 8]] == 0)
					{
						PC += 4;
					}	
					else
					{
						PC += 2;
					}
					break;

				default:
					printf("Unknown opcode [0xE000]: 0x%X\n", opcode);
					break;
			}
			break;

		case 0xF000: 
			switch (opcode & 0x00FF)
			{
				case 0x0007:	// FX07: Sets VX to the value of the delay timer 
					V[(opcode & 0x0F00) >> 8] = delay_timer;
					PC += 2;
					break;

				case 0x000A:	// FX0A: A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
					bool key_press = false;

					for (int i = 0; i < 1; ++i)
					{
						if (key[i] != 0)		// Check all keys in array
						{
							V[(opcode & 0x0F00) >> 8] = i;
							key_press = true;
						}
					}

					if (!key_press)				// The empty return statement is like recursive function. Case will be called again and again as long as key_press = false
					{
						return;
					}

					PC += 2;
					break;

				case 0x0015:						// FX15: Sets the delay timer to VX
					delay_timer = V[(opcode & 0x0F00) >> 8];
					PC += 2;
					break;

				case 0x0018:						// FX18: Sets the sound timer to VX
					sound_timer = V[(opcode & 0x0F00) >> 8];
					PC += 2;
					break;

				case 0x001E:						// FX1E: Adds VX to I. VF is set to 1 when there is a range overflow (I + VX>0xFFF), and to 0 when there isn't.
					if ((I + V[(opcode & 0x0F00) >> 8]) > 0xFFF)
					{
						V[0xF] = 1;
					}
					else
					{
						V[0xF] = 0;
					}
					I += V[(opcode & 0x0F00) >> 8];
					PC += 2;
					break;

				case 0x0029:						// FX29: Sets I to the location of the sprite for the character in VX. Characters 0-F [HEX] are represented by a 4x5 font.
					I = V[(opcode & 0x0F00) >> 8] * 0x5;		// * 0x5 because sprites are 5-bytes long and we must to store every byte of a sprite 
					PC += 2;
					break;

				case 0x0033:						// FX33: Store the binary-coded decimal representation of VX, with the most significant of three digits at the adress in I,
													// the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representa-
													// tion of VX, place the hundreds digit in memory at location in I, the tens digit at lovation I+1, and the ones digit at 
													// at location I+2
					memory[I]     =  V[(opcode & 0x0F00) >> 8] / 100;			 // For example 253: 253 / 100 = 2; we got the most significant digit. YEAH !!!!
					memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;		 // For example 253: 253 / 10 = 25; 25 % 10 = 5; we got the middle digit. YEAH !!!!  
					memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;		 // For example 253: 253 % 100 = 53; 53 % 10 = 3; we got the least significant digit. YEAH !!!!
					PC += 2;
					break;

				case 0x0055:						// FX55: Stores V0 to VX (including VX) in memory starting at address I. The offset from I
													// is increased by 1 for each value written, but itself is left unmodified.
					for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
					{
						memory[I + i] = V[i];
					}
					I += ((opcode & 0x0F00) >> 8) + 1;			// I dont know what the need of this line, but i found information that 
					PC += 2;									// On the original interpreter, when the operation is done, I = I + X + 1.
					break;

				case 0x0065:						// Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I
													// is increased by 1 for each value written, but itself is left unmodified
					for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
					{
						V[i] = memory[I + i];
					}
					I += ((opcode & 0x0F00) >> 8) + 1;			// I dont know what the need of this line, but i found information that 
					PC += 2;									// On the original interpreter, when the operation is done, I = I + X + 1.
					break;


				default:
					printf("Unknown opcode [0xF000]: 0x%X\n", opcode);
					break;
			}
			break;

		default:
			printf("Unknown opcode: 0x%X\n", opcode);
			break;
	}		

	// 
	if (delay_timer > 0)
		--delay_timer;

	if (sound_timer > 0)
	{
		if (sound_timer == 1)
			printf("BEEP !\n");
		--sound_timer;
	}
}							

// 364 367 391-398 DXYN - dont understand