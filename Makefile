# Cross-platform wrapper around CMake presets.
# Auto-picks a preset based on the host OS. Override with: make build PRESET=linux-clang

ifeq ($(OS),Windows_NT)
    PRESET ?= windows-clang
    BIN_EXT := .exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        PRESET ?= macos-clang
    else
        PRESET ?= linux-clang
    endif
    BIN_EXT :=
endif

BUILD_DIR := build

.PHONY: configure build run test clean format lint bootstrap help

## configure: run CMake configure step for the current OS preset
configure:
	cmake --preset $(PRESET)

## build: configure + compile
build: configure
	cmake --build --preset $(PRESET)

## run: build and run the main binary
run: build
	./$(BUILD_DIR)/low-latency$(BIN_EXT)

## test: build and run all unit tests
test: build
	ctest --preset $(PRESET)

## clean: nuke the build directory
clean:
	cmake -E rm -rf $(BUILD_DIR)

## format: auto-format all C++ sources with clang-format (must be on PATH)
format:
	cmake -E chdir . clang-format -i $(shell cmake -E ls src include tests 2>/dev/null || echo)

## lint: clang-tidy over src + tests (reads compile_commands.json from $(BUILD_DIR))
lint: build
	clang-tidy -p $(BUILD_DIR) src/*.cpp tests/*.cpp

## bootstrap: install vcpkg deps declared in vcpkg.json (first-time setup)
bootstrap:
	cmake --preset $(PRESET)

## help: list targets
help:
	@grep -E '^##' Makefile | sed 's/## //'
