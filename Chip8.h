#pragma once
#include <cstdint>
#include <string>
#include "Keyboard.h"

struct Instruction {
	uint8_t opcode;
	uint8_t X_regaddr;
	uint8_t Y_regaddr;
	uint8_t N_operand;
	uint8_t NN_operand;
	uint16_t NNN_operand;

	Instruction(uint16_t);
};

class Chip8
{
private:
	uint8_t memory[4096];
	uint16_t pc;
	uint16_t I;
	uint8_t delay_timer;
	uint8_t sound_timer;
	uint8_t v_register[16];
	uint16_t stack[16];
	uint16_t sp;
	Keyboard keyboard;

public:
	uint8_t display[64 * 32];

private:
	typedef void (Chip8::* func_ptr)(const Instruction&);
	func_ptr decode(const Instruction&);
	void load_fontset();

	void opcode_00E0(const Instruction&);
	void opcode_00EE(const Instruction&);
	void opcode_0NNN(const Instruction&);
	void opcode_1NNN(const Instruction&);
	void opcode_2NNN(const Instruction&);
	void opcode_3XNN(const Instruction&);
	void opcode_4XNN(const Instruction&);
	void opcode_5XY0(const Instruction&);
	void opcode_6XNN(const Instruction&);
	void opcode_7XNN(const Instruction&);
	void opcode_8XY0(const Instruction&);
	void opcode_8XY1(const Instruction&);
	void opcode_8XY2(const Instruction&);
	void opcode_8XY3(const Instruction&);
	void opcode_8XY4(const Instruction&);
	void opcode_8XY5(const Instruction&);
	void opcode_8XY6(const Instruction&);
	void opcode_8XY7(const Instruction&);
	void opcode_8XYE(const Instruction&);
	void opcode_9XY0(const Instruction&);
	void opcode_ANNN(const Instruction&);
	void opcode_BNNN(const Instruction&);
	void opcode_CXNN(const Instruction&);
	void opcode_DXYN(const Instruction&);
	void opcode_EX9E(const Instruction&);
	void opcode_EXA1(const Instruction&);
	void opcode_FX07(const Instruction&);
	void opcode_FX0A(const Instruction&);
	void opcode_FX15(const Instruction&);
	void opcode_FX18(const Instruction&);
	void opcode_FX1E(const Instruction&);
	void opcode_FX29(const Instruction&);
	void opcode_FX33(const Instruction&);
	void opcode_FX55(const Instruction&);
	void opcode_FX65(const Instruction&);
	void opcode_NOOP(const Instruction&);
public:
	Chip8();
	void cpu_cycle();
	void load_rom(const std::string& filename);
};