# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liamsycamore/Documents/Arduino_Test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liamsycamore/Documents/Arduino_Test/bin

# Utility rule file for bin2hex.

# Include the progress variables for this target.
include blinkLED/CMakeFiles/bin2hex.dir/progress.make

blinkLED/CMakeFiles/bin2hex:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liamsycamore/Documents/Arduino_Test/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating HEX image"
	cd /Users/liamsycamore/Documents/Arduino_Test/bin/blinkLED && avr-objcopy -O ihex -R .eeprom blinkLED blinkLED.hex

bin2hex: blinkLED/CMakeFiles/bin2hex
bin2hex: blinkLED/CMakeFiles/bin2hex.dir/build.make

.PHONY : bin2hex

# Rule to build all files generated by this target.
blinkLED/CMakeFiles/bin2hex.dir/build: bin2hex

.PHONY : blinkLED/CMakeFiles/bin2hex.dir/build

blinkLED/CMakeFiles/bin2hex.dir/clean:
	cd /Users/liamsycamore/Documents/Arduino_Test/bin/blinkLED && $(CMAKE_COMMAND) -P CMakeFiles/bin2hex.dir/cmake_clean.cmake
.PHONY : blinkLED/CMakeFiles/bin2hex.dir/clean

blinkLED/CMakeFiles/bin2hex.dir/depend:
	cd /Users/liamsycamore/Documents/Arduino_Test/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liamsycamore/Documents/Arduino_Test /Users/liamsycamore/Documents/Arduino_Test/blinkLED /Users/liamsycamore/Documents/Arduino_Test/bin /Users/liamsycamore/Documents/Arduino_Test/bin/blinkLED /Users/liamsycamore/Documents/Arduino_Test/bin/blinkLED/CMakeFiles/bin2hex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : blinkLED/CMakeFiles/bin2hex.dir/depend
