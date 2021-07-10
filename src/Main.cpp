#include "Screen.h"
#include "Chip8.h"
#include "Audio.h"
#include "CycleSynchronizationTimer.h"
#include "Keyboard.h"
#include "Helper.h"

int window_size_scale = 10;
int cycles_per_second = 600;
bool quit_flag = false;
bool mute_flag = false;
const char* default_game = "pong.ch8";

int main(int argc, char* argv[])
{
	// get optional [-s cycles_per_second] command line argument
	const char* cycles_per_second_flag = get_commandline_flags(argv, argv + argc, "-s");
	if (cycles_per_second_flag)
		cycles_per_second = atoi(cycles_per_second_flag);

	// get optional [-s window_size_scale] command line argument
	const char* window_size_scale_flag = get_commandline_flags(argv, argv + argc, "-w");
	if (window_size_scale_flag)
		window_size_scale = atoi(window_size_scale_flag);

	// Initialize emulator and I/O
	Chip8 emulator;
	Screen screen(window_size_scale);
	Audio audio;
	Keyboard keyboard;

	// If [file_path] command line argument is a valid file, use [file_path], else use pong.ch8 as default
	if (argc >= 2 && file_exists(argv[1]))
		emulator.load_rom(argv[1]);
	else
		emulator.load_rom(default_game);

	// Main emulation loop
	for (unsigned int i = 0; !quit_flag ; i++) 
	{
		CycleSynchronizationTimer syncrhonize_cycles_per_second(cycles_per_second);
		keyboard.update_keyboard_state(emulator.keyboard_state, quit_flag, mute_flag);
		emulator.cpu_cycle();
		if (emulator.display_updated) screen.draw(emulator.display);

		if (i % (cycles_per_second / 60) == 0)
		{
			emulator.decrement_timers();
			if (emulator.sound_timer > 0 && !mute_flag) audio.Beep();
		}
	}

	return 0;
}