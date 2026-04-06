# ── Paths ─────────────────────────────────────────────────────────
LLVM_BIN     := /opt/homebrew/opt/llvm/bin
CLANG_FORMAT := $(LLVM_BIN)/clang-format
CLANG_TIDY   := $(LLVM_BIN)/clang-tidy
VCPKG_ROOT   := $(CURDIR)/vcpkg
BUILD_DIR    := build

# ── Targets ───────────────────────────────────────────────────────

.PHONY: build run clean format lint test configure

## configure: run CMake configure step (vcpkg toolchain)
configure:
	cmake -B $(BUILD_DIR) \
		-DCMAKE_TOOLCHAIN_FILE=$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

## build: configure + compile everything
build: configure
	cmake --build $(BUILD_DIR) -j $$(sysctl -n hw.ncpu)

## run: build and run the main binary
run: build
	./$(BUILD_DIR)/low-latency

## test: build and run all unit tests
test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

## clean: nuke the build directory
clean:
	rm -rf $(BUILD_DIR)

## format: auto-format all C++ source files
format:
	find src include tests -name '*.cpp' -o -name '*.hpp' | xargs $(CLANG_FORMAT) -i

## lint: run clang-tidy on all source files
lint: build
	find src tests -name '*.cpp' | xargs $(CLANG_TIDY) -p $(BUILD_DIR)

## help: show this help
help:
	@grep -E '^##' Makefile | sed 's/## //'
