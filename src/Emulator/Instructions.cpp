#include "Chip8.h"

// CLS - clear display pixels
void Chip8::opcode_00E0(const Instruction& instr)
{	
	display_updated = true;
	memset(display, 0, sizeof(display));
}

// RET - return from subroutine
void Chip8::opcode_00EE(const Instruction& instr)
{
	sp--;
	pc = stack[sp];
}

// SYS addr - jump to machine code instruction (not implemented)
void Chip8::opcode_0NNN(const Instruction& instr) {}

// JUMP addr - jump to NNN
void Chip8::opcode_1NNN(const Instruction& instr)
{
	pc = instr.NNN_operand;
}

// CALL addr - calls subroutine at NNN
void Chip8::opcode_2NNN(const Instruction& instr)
{
	stack[sp] = pc;
	sp++;	
	pc = instr.NNN_operand;
}

// SKIPEQUALS Vx, byte
void Chip8::opcode_3XNN(const Instruction& instr)
{
	if (v_register[instr.X_regaddr] == instr.NN_operand)
		pc += 2;
}

// SKIPNOTEQUALS Vx, byte - skip if VX != NN
void Chip8::opcode_4XNN(const Instruction& instr)
{
	if (v_register[instr.X_regaddr] != instr.NN_operand)
		pc += 2;
}

// SKIPEQUALS Vx, Vy
void Chip8::opcode_5XY0(const Instruction& instr)
{
	if (v_register[instr.X_regaddr] == v_register[instr.Y_regaddr])
		pc += 2;
}

// LOAD Vx, byte
void Chip8::opcode_6XNN(const Instruction& instr)
{
	v_register[instr.X_regaddr] = instr.NN_operand;
}

// ADD Vx, byte
void Chip8::opcode_7XNN(const Instruction& instr)
{
	v_register[instr.X_regaddr] += instr.NN_operand;
}

// LOAD Vx, Vy
void Chip8::opcode_8XY0(const Instruction& instr)
{
	v_register[instr.X_regaddr] = v_register[instr.Y_regaddr];
}

// OR Vx, Vy
void Chip8::opcode_8XY1(const Instruction& instr)
{
	v_register[instr.X_regaddr] |= v_register[instr.Y_regaddr];
}

// AND Vx, Vy
void Chip8::opcode_8XY2(const Instruction& instr)
{
	v_register[instr.X_regaddr] &= v_register[instr.Y_regaddr];
}

// XOR Vx, Vy
void Chip8::opcode_8XY3(const Instruction& instr)
{
	v_register[instr.X_regaddr] ^= v_register[instr.Y_regaddr];
}

// ADD Vx, Vy
void Chip8::opcode_8XY4(const Instruction& instr)
{
	uint16_t sum = v_register[instr.X_regaddr] + v_register[instr.Y_regaddr];
	v_register[0xF] = 0;
	if (sum > 255){
		v_register[0xF] = 1;
	}
	v_register[instr.X_regaddr] = sum & 0xFF;
}

// SUB Vx, Vy
void Chip8::opcode_8XY5(const Instruction& instr)
{
	if (v_register[instr.X_regaddr] > v_register[instr.Y_regaddr])
		v_register[0xF] = 1;
	else{
		v_register[0xF] = 0;
	}
	v_register[instr.X_regaddr] -= v_register[instr.Y_regaddr];
}

// SHIFTRIGHT Vx
void Chip8::opcode_8XY6(const Instruction& instr)
{	
	v_register[0xF] = v_register[instr.X_regaddr] & 0x1;
	v_register[instr.X_regaddr] >>= 1;
}

// SUBN Vx, Vy
void Chip8::opcode_8XY7(const Instruction& instr)
{
	if (v_register[instr.X_regaddr] < v_register[instr.Y_regaddr])
		v_register[0xF] = 1;
	else{
		v_register[0xF] = 0;
	}
	v_register[instr.X_regaddr] = v_register[instr.Y_regaddr] - v_register[instr.X_regaddr];
}

// SHIFTLEFT Vx
void Chip8::opcode_8XYE(const Instruction& instr)
{
	v_register[0xF] = (v_register[instr.X_regaddr] & 0x80) >> 7;
	v_register[instr.X_regaddr] <<= 1;
}

// SKIPNOTEQUALS Vx, Vy
void Chip8::opcode_9XY0(const Instruction& instr)
{
	if (v_register[instr.X_regaddr] != v_register[instr.Y_regaddr])
		pc += 2;
}

// LOAD I, NNN
void Chip8::opcode_ANNN(const Instruction& instr)
{
	I = instr.NNN_operand;
}

// JUMP V0, NNN
void Chip8::opcode_BNNN(const Instruction& instr)
{
	pc = instr.NNN_operand + v_register[0];
}

// RANDOM Vx, NN
void Chip8::opcode_CXNN(const Instruction& instr)
{
	v_register[instr.X_regaddr] = (rand() % 0xFF) & instr.NN_operand;
}

// DRAW SPRITE
#define BIT_ON(byte,pos) ((byte >> (7 - pos)) & 1)
void Chip8::opcode_DXYN(const Instruction& instr)
{
	display_updated = true;
	// Set the xpos and ypos to the value in VX and VY modulo 64 and 32
	auto x_pos = v_register[instr.X_regaddr] % 64;
	auto y_pos = v_register[instr.Y_regaddr] % 32;


	// Height of sprite
	auto height = instr.N_operand;

	// Set VF to 0
	v_register[0xF] = 0;

	for (int dy = 0; dy < height && y_pos + dy < 32; dy++)
	{
		auto sprite_byte = memory[I + dy];
		for (int dx = 0; dx < 8 && x_pos + dx < 64; dx++)
		{
			if (BIT_ON(sprite_byte, dx))
			{
				auto pixel_adress = (y_pos + dy) * 64 + (x_pos + dx);

				// If display pixel was on and is turned off, we set register 0xF to 1
				if (display[pixel_adress] == 0xFF)
					v_register[0xF] = 1;

				// XOR the display pixel
				display[pixel_adress] ^= 0xFF;
			}
		}
	}
}

// SKIPIFKEY Vx
void Chip8::opcode_EX9E(const Instruction& instr)
{
	if (keyboard_state[v_register[instr.X_regaddr]])
		pc += 2;
}

// SKIPIFNOTKEY Vx
void Chip8::opcode_EXA1(const Instruction& instr)
{
	if (!keyboard_state[v_register[instr.X_regaddr]])
		pc += 2;
}

// lOAD Vx, delay_timer
void Chip8::opcode_FX07(const Instruction& instr)
{
	v_register[instr.X_regaddr] = delay_timer;
}

// LOAD Vx, keypress (polled)
void Chip8::opcode_FX0A(const Instruction& instr)
{
	bool found = false;
	for (int i = 0; (i < 16 || !found); i++)
	{
		if (keyboard_state[i])
		{
			v_register[instr.X_regaddr] = i;
			found = true;
		}
	}
	if (!found) pc -= 2;
}

// LOAD delay_timer, Vx
void Chip8::opcode_FX15(const Instruction& instr)
{
	delay_timer = v_register[instr.X_regaddr];
}

// LOAD sound_timer, Vx
void Chip8::opcode_FX18(const Instruction& instr)
{
	sound_timer = v_register[instr.X_regaddr];
}

// ADD I, Vx
void Chip8::opcode_FX1E(const Instruction& instr)
{
	I += v_register[instr.X_regaddr];
}

// LOAD I, 0x50 + Vx * 5
void Chip8::opcode_FX29(const Instruction& instr)
{
	I = 0x50 + (v_register[instr.X_regaddr] * 5);
}

// LOAD memory[I], BCD(Vx)
void Chip8::opcode_FX33(const Instruction& instr)
{
	auto value = v_register[instr.X_regaddr];
	memory[I + 2] = value % 10;
	memory[I + 1] = (value / 10) % 10;
	memory[I] = (value / 100) % 10;
}

// LOAD memory[I], V0...Vx
void Chip8::opcode_FX55(const Instruction& instr)
{
	for (auto i = 0; i <= instr.X_regaddr; i++)
		memory[I + i] = v_register[i];
	}

// LOAD V0...Vx, memory[I]
void Chip8::opcode_FX65(const Instruction& instr)
{
	for (auto i = 0; i <= instr.X_regaddr; i++)
		v_register[i] = memory[I + i];
}

void Chip8::opcode_NOOP(const Instruction& instr) {};