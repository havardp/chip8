# Chip8 Emulator
This is an emulator written in c++, using SDL2 blabla. Includes audio blabla

[IMAGE OF GAME]

## Building on windows
add msbuild to path https://docs.microsoft.com/en-us/visualstudio/msbuild/whats-new-msbuild-16-0?view=vs-2019
add cmake to path
add sdl2 to CMAKE_PREFIX_PATH

cmake -S . -B build

cmake --build build --config Release

## Building on linux

sudo apt install cmake libsdl2-dev g++

## Usage
```
Chip8 [filename] ...
```

press m to mute
press p to pause

## Resources

## License