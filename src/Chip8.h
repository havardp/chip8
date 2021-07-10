#pragma once
#include <cstdint>
#include <string>

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
	uint8_t v_register[16];
	uint16_t stack[16];
	uint16_t sp;
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

public:
	uint8_t display[64 * 32];
	uint8_t sound_timer;
	bool display_updated;
	bool keyboard_state[16];

private:
	typedef void (Chip8::* func_ptr)(const Instruction&);
	func_ptr decode(const Instruction&);

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
	void decrement_timers();
};