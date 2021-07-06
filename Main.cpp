#include "Screen.h"
#include "Chip8.h"
#include "Audio.h"
#include "CycleSynchronizationTimer.h"

constexpr int window_size_scale = 10;
constexpr int cycles_per_second = 700;
const char* rom_name = "roms/games/Pong.CH8";

int main(int argc, char* argv[])
{
	Chip8 emulator;
	emulator.load_rom(rom_name);

	Screen screen(window_size_scale);
	Audio audio;

	for (;;) {
		CycleSynchronizationTimer syncrhonize_cycles_per_second(cycles_per_second);

		emulator.cpu_cycle();

		if (emulator.display_updated)
			screen.draw(emulator.display);

		audio.play_sound_if_sound_timer_greater_than_zero(emulator.sound_timer);
	}
}