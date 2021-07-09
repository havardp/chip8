#include "Chip8.h"
#include <fstream>

Chip8::Chip8() : 
	memory{},
	pc(0x200),
	v_register{},
	I(0),
	delay_timer(0),
	sound_timer(0),
	display{},
	stack{},
	sp(0)
{
	load_fontset();
}

void Chip8::load_fontset()
{
	uint8_t chip8_fontset[80] =
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
	for (int i = 0; i < 80; i++)
		memory[0x50 + i] = chip8_fontset[i];
}

void Chip8::cpu_cycle(int cycles_per_second)
{
	// fetch instruction
	Instruction instr((memory[pc] << 8) | memory[pc + 1]);

	// Increment program counter
	pc += 2;

	// Set display as not updated by default
	display_updated = false;
	
	// Decode instruction
	func_ptr opcode_function_ptr = decode(instr);

	// Execute instruction
	(this->*opcode_function_ptr)(instr);
}

void Chip8::decrement_timers()
{
	if (sound_timer > 0) sound_timer--;
	if (delay_timer > 0) delay_timer--;
}

// maps the instruction to the corresponding execute function pointer
Chip8::func_ptr Chip8::decode(const Instruction& instr) 
{
	switch (instr.opcode)
	{
	case 0x0:
		switch (instr.NNN_operand) 
		{
		case 0x0E0:
			return &Chip8::opcode_00E0;
		case 0x0EE:
			return &Chip8::opcode_00EE;
		default:
			return &Chip8::opcode_0NNN;
		}

	case 0x1:
		return &Chip8::opcode_1NNN;

	case 0x2:
		return &Chip8::opcode_2NNN;

	case 0x3:
		return &Chip8::opcode_3XNN;

	case 0x4:
		return &Chip8::opcode_4XNN;

	case 0x5:
		switch (instr.N_operand)
		{
		case 0x0:
			return &Chip8::opcode_5XY0;
		default:
			return &Chip8::opcode_NOOP;
		}

	case 0x6:
		return &Chip8::opcode_6XNN;

	case 0x7:
		return &Chip8::opcode_7XNN;

	case 0x8:
		switch (instr.N_operand)
		{
		case 0x0:
			return &Chip8::opcode_8XY0;
		case 0x1:
			return &Chip8::opcode_8XY1;
		case 0x2:
			return &Chip8::opcode_8XY2;
		case 0x3:
			return &Chip8::opcode_8XY3;
		case 0x4:
			return &Chip8::opcode_8XY4;
		case 0x5:
			return &Chip8::opcode_8XY5;
		case 0x6:
			return &Chip8::opcode_8XY6;
		case 0x7:
			return &Chip8::opcode_8XY7;
		case 0xE:
			return &Chip8::opcode_8XYE;
		}

	case 0x9:
		switch (instr.N_operand)
		{
		case 0x0:
			return &Chip8::opcode_9XY0;
		default:
			return &Chip8::opcode_NOOP;
		}

	case 0xA:
		return &Chip8::opcode_ANNN;

	case 0xB:
		return &Chip8::opcode_BNNN;

	case 0xC:
		return &Chip8::opcode_CXNN;

	case 0xD:
		return &Chip8::opcode_DXYN;

	case 0xE:
		switch (instr.NN_operand)
		{
		case 0x9E:
			return &Chip8::opcode_EX9E;
		case 0xA1:
			return &Chip8::opcode_EXA1;
		default:
			return &Chip8::opcode_NOOP;
		}

	case 0xF:
		switch (instr.NN_operand)
		{
		case 0x07:
			return &Chip8::opcode_FX07;
		case 0x0A:
			return &Chip8::opcode_FX0A;
		case 0x15:
			return &Chip8::opcode_FX15;
		case 0x18:
			return &Chip8::opcode_FX18;
		case 0x1E:
			return &Chip8::opcode_FX1E;
		case 0x29:
			return &Chip8::opcode_FX29;
		case 0x33:
			return &Chip8::opcode_FX33;
		case 0x55:
			return &Chip8::opcode_FX55;
		case 0x65:
			return &Chip8::opcode_FX65;
		default:
			return &Chip8::opcode_NOOP;
		}

	default:
		return &Chip8::opcode_NOOP;
	}
}

void Chip8::load_rom(const std::string& filename)
{
	std::ifstream rom(filename, std::ifstream::binary);
	if (rom) {
		// set up buffer and length
		rom.seekg(0, rom.end);
		std::streamoff length = rom.tellg();
		char* buffer = new char[length];

		// read binary rom into buffer
		rom.seekg(0, rom.beg);
		rom.read(buffer, length);
		rom.close();

		// fill memory with instructions from position 0x200 (512 in decimal)
		for (int i = 0; i < length; i++)
			memory[0x200 + i] = buffer[i];

		delete[] buffer;
	}
	else
	{
		throw std::invalid_argument("Couldn't read ROM file.");
	}
}
