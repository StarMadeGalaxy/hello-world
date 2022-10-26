class IlyukChip8
{
	public:

		void IlyukEmulateCycle();		// Description of all opcodes and their fetch-decode-execute 
		bool drawFlag;					// I HAVE NO FUCKING IDEA FOR WHAT IT IS NEEDED FOR (. )(. )

		// The chip-8 has a Hex based keypad (0x0 - 0xF), we can use an array to store the current state of the key
		unsigned char key[16];
		// Original chip-8 display resolution is 64x32 pixels.
		unsigned char graphics[64 * 32];

	private:
		// chip-8 has 4096 memory in total
		unsigned char memory[4096];
		// chip-8 has 35 opcodes, which are all two bytes long and stored big-endian
		unsigned short opcode;
		// chip-8 has 15 GPR (general-purpose registers) V0-VE in hex, the 16th register is used for the carry flag
		unsigned char V[16];
		// The address register which is named I, is 2-bytes wide and is used with several opcodes that involve memory operations
		unsigned short I;
		// PC is 'pseudo-register', which are not accessable from chip-8 programs. The program should be 16-bit
		// and is used to store the currently executing address.
		unsigned short PC;
		// The sound timer is active whenever the sound time register (ST) is non-zero. This timer also decrements at a rate of 60Hz
		// however, as long as ST's value is greater than zero, the Chip-8 buzzer will sound. When ST reaches zero, the timer deactivates 
		unsigned char sound_timer;
		// The delay times is activate whenever the delay time register (DT) is non-zero. This timer does nothing more than subtract 1 from the 
		// value of DT at a rate of 60 Hz. When DT reaches 0, it deactivates.
		unsigned char delay_timer;
		// The stack pointer can be 8-bit, its used to point the topmost level of the stack 
		unsigned char SP;
		// The stack is an array of 16 16-bit values, used to store the address that the interpreter should return to when finished with a subroutine. 
		// Chip-8 allows for up to 16 levels of nested subroutines.
		unsigned short stack[16];

		void initialize();
};

