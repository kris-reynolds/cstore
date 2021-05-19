
.PHONY: setup-dev setup-rel all-dev all-rel test

setup-dev:
	@mkdir -p build/dev
	cd build/dev && \
	cmake \
		-DCMAKE_BUILD_TYPE=RelWithDebInfo \
		-DENABLE_SANITIZER_ADDRESS=TRUE \
		-DENABLE_SANITIZER_LEAK=TRUE \
		-DENABLE_SANITIZER_UNDEFINED_BEHAVIOR=TRUE \
		../../

setup-rel:
	@mkdir -p build/rel
	cd build/rel && \
	cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DENABLE_TESTING=OFF \
		../../

all-dev:
	@cd build/dev && make

all-rel:
	@cd build/rel && make

test: all-dev
	@cd build/dev && ctest
