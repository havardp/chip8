#include "Screen.h"
#include "Chip8.h"
#include "Audio.h"
#include "CycleSynchronizationTimer.h"

constexpr int window_size_scale = 10;
constexpr int cycles_per_second = 600;
constexpr const char* rom_name = "roms/games/Pong.CH8";

int main(int argc, char* argv[])
{
	Chip8 emulator;
	emulator.load_rom(rom_name);

	Screen screen(window_size_scale);
	Audio audio;

	for (;;) 
	{
		for (int i = 0; i < cycles_per_second / 60; i++)
		{
			CycleSynchronizationTimer syncrhonize_cycles_per_second(cycles_per_second);

			emulator.cpu_cycle(cycles_per_second);
			if (emulator.display_updated)
				screen.draw(emulator.display);
		}

		emulator.decrement_timers();
		if (emulator.sound_timer > 0)
			audio.Beep();
	}
	
}