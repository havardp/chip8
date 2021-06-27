#include "Screen.h"
#include "Chip8.h"
#include <Windows.h> // remove when i do timing correctly, only used for sleep

int main(int argc, char* argv[]) 
{	
	Chip8 emulator;
	emulator.load_rom("roms/games/Pong.CH8");

	Screen screen(10);

	// TODO play audio
	// TODO proper timing handling, timers decrement at 60hz, emulator plays at 700fps ish

	for (;;) {
		emulator.cpu_cycle();
		screen.draw(emulator.display);
		Sleep(10);
	}
}