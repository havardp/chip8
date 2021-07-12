# Chip8 Emulator
This is an emulator written in c++, using SDL2 blabla. Includes audio blabla

[IMAGE OF GAME]

## Prerequisites 

#### Windows
install buildtools (comes with VS) https://docs.microsoft.com/en-us/visualstudio/msbuild/whats-new-msbuild-16-0?view=vs-2019

add cmake to path 

add sdl2 to CMAKE_PREFIX_PATH

#### Linux
```
sudo apt install cmake libsdl2-dev g++
```

## Building and compiling
```
cmake -S . -B build

cmake --build build --config Release	
```

OR just launch it in any IDE and it will recognize the cmake file ¯\\\_(ツ)\_/¯
## Usage
```
Chip8 [filename] ...
```

press m to mute
press p to pause

## Resources

## License

C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe