cmake_minimum_required(VERSION 2.8.4)

project(Chip8)

find_package(SDL2 REQUIRED)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_LIST_DIR}/bin")

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES 
	src/main.cpp
	src/Emulator/Chip8.cpp
	src/Emulator/Chip8.h
	src/Emulator/Instructions.cpp
	src/IO/Audio.cpp
	src/IO/Audio.h
	src/IO/Keyboard.cpp
	src/IO/Keyboard.h
	src/IO/Screen.cpp
	src/IO/Screen.h
	src/Timer/CycleSynchronizationTimer.cpp
	src/Timer/CycleSynchronizationTimer.h
	src/Util/Helper.cpp
	src/Util/Helper.h
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# WINDOWS ONLY - Copy SDL.dll and roms/ folder to bin/ folder
IF (WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_INCLUDE_DIRS}/../lib/x64/SDL2.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
	  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/roms ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/roms

	  # Output Message
	  COMMENT "Copying SDL binary from ${SDL2_INCLUDE_DIRS}../lib/x64/SDL2.dll and rom folder to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}" VERBATIM
	)
ENDIF()