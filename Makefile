

.PHONY: setup



setup:
	@mkdir -p build
	@cd build && \
	cmake \
		-DENABLE_SANITIZER_ADDRESS=TRUE \
		-DENABLE_SANITIZER_LEAK=TRUE \
		-DENABLE_SANITIZER_UNDEFINED_BEHAVIOR=TRUE \
		-DENABLE_CPPCHECK=ON \
		-DENABLE_CLANG_TIDY=ON \
		../

all:
	@cd build && make

test: all
	@cd build && ctest