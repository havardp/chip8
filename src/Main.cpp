#include "Emulator/Chip8.h"
#include "IO/Screen.h"
#include "IO/Audio.h"
#include "IO/Keyboard.h"
#include "Timer/CycleSynchronizationTimer.h"
#include "Util/Helper.h"

int window_size_scale = 10;
int cycles_per_second = 600;
bool quit_flag = false;
bool mute_flag = false;
const char* default_game = "breakout.ch8";

int main(int argc, char* argv[])
{
	// get optional [-s cycles_per_second] command line argument
	const char* cycles_per_second_flag = get_commandline_flags(argv, argv + argc, "-s");
	if (cycles_per_second_flag)
		cycles_per_second = atoi(cycles_per_second_flag);

	// get optional [-w window_size_scale] command line argument
	const char* window_size_scale_flag = get_commandline_flags(argv, argv + argc, "-w");
	if (window_size_scale_flag)
		window_size_scale = atoi(window_size_scale_flag);

	// Initialize emulator and I/O
	Chip8 emulator;
	Screen screen(window_size_scale);
	Audio audio;
	Keyboard keyboard;

	// If [file_path] command line argument is a valid file, load [file_path] as rom, else load pong.ch8 rom as default
	if (argc >= 2 && file_exists(argv[1]))
		emulator.load_rom(argv[1]);
	else
		emulator.load_rom(default_game);

	// Main emulation loop
	for (unsigned int i = 0; !quit_flag ; i++) 
	{
		// Synchronize so that one cycle takes *cycle_per_second* cycles per second
		CycleSynchronizationTimer syncrhonize_cycles_per_second(cycles_per_second);
		// Update keyboard state and set potential quit or mute flags
		keyboard.update_keyboard_state(emulator.keyboard_state, quit_flag, mute_flag);
		// Run a cpu cycle / opcode
		emulator.cpu_cycle();
		// Update the screen if the display array has changed
		if (emulator.display_updated) 
			screen.draw(emulator.display);

		// this codeblock gets run 60 times a second, independent of cycles per second
		if (i % (cycles_per_second / 60) == 0)
		{
			// decrement sound and delay timers
			emulator.decrement_timers();
			// play beeping sound if sound timer and not mute flag
			if (emulator.sound_timer > 0 && !mute_flag) 
				audio.Beep();
		}
	}

	return 0;
}