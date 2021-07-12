cmake_minimum_required(VERSION 2.8.4)

project(Chip8)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES 
	src/Main.cpp
	src/Emulator/Chip8.cpp
	src/Emulator/Instructions.cpp
	src/IO/Audio.cpp
	src/IO/Keyboard.cpp
	src/IO/Screen.cpp
	src/Timer/CycleSynchronizationTimer.cpp
	src/Util/Helper.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Copy roms/ folder into /bin
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/roms ${EXECUTABLE_OUTPUT_PATH}/roms

  # Output Message
  COMMENT "Copying roms to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}" VERBATIM
)

# WINDOWS ONLY - Copy SDL.dll to bin/ folder
IF (WIN32)

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_INCLUDE_DIRS}/../lib/x64/SDL2.dll ${EXECUTABLE_OUTPUT_PATH}

	  # Output Message
	  COMMENT "Copying SDL binary from ${SDL2_INCLUDE_DIRS}../lib/x64/SDL2.dll to ${EXECUTABLE_OUTPUT_PATH}" VERBATIM
	)
ENDIF()
