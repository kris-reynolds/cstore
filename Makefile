
BUILD_TYPE ?= RelWithDebInfo

.PHONY: setup

setup:
	@mkdir -p build
	cd build && \
	cmake \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DENABLE_SANITIZER_ADDRESS=FALSE \
		-DENABLE_SANITIZER_LEAK=FALSE \
		-DENABLE_SANITIZER_UNDEFINED_BEHAVIOR=FALSE \
		../

all:
	@cd build && make

test: all
	@cd build && ctest
