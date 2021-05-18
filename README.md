# cstore

[![CI](https://github.com/kris-reynolds/cstore/actions/workflows/test.yml/badge.svg)](https://github.com/kris-reynolds/cstore/actions/workflows/test.yml)

Container library for C.

`cstore` provides various common container implementations in C.  In order to cater to the typical C use case (embedded devices) the developer can provide their own memory buffer, or allow the library to manage the memory for them.

Through macros "type safe" container accessors/modifiers can be generated.  However they currently come at the cost of an extra re-direct.

**Under Construction**

This project is still in early phases of development.  The API can (and will) change, and more containers will be added as time allows.  Unit tests with reasonable coverage should be added before you can use any of these containers with confidence.

## Example

```c
#include "cstore/vector.h"

typedef struct foo_t {
    int bar;
} foo;

CREATE_VECTOR_FUNCS(foo);
int main() {
    vector v = new_heap_vector_foo();

    for(int i = 0; i < 10; ++i) {
        foo* f = vector_push_back(&v, NULL);
        f->bar = i;
    }

    for(int i = 0; i < 10; ++i) {
        foo* f = vector_at(&v, i);
        printf("%d\n", f->bar);
    }
    vector_delete(&v);
}
```

Using user provided memory:

```c
int buffer[128]
int capacity = sizeof(buffer) / sizeof(foo);
vector v = new_vector_foo(capacity, buffer);

for(int i = 0; i < 10; ++i) {
    foo* f = vector_push_back(&v, NULL);
    f->bar = i;
}

for(int i = 0; i < 10; ++i) {
    foo* f = vector_at(&v, i);
    printf("%d\n", f->bar);
}
```

## Goals

- Minimal binary footprint
-    Optional support for additional type saftey (macro defined functions)
- Support for fixed memory sizes
- No dependencies (Outside UT frameworks)
- Platform agnostic

## Infrastructure

- [ ] Documentation generation through Doxygen
- [ ] CMake install infrastructure
- [ ] Code Coverage
- [ ] Container builds for varying compiler versions

### Containers

- [x] Vector
- [x] Ring Buffer
- [ ] Stack
- [x] Single Linked List
- [ ] Set (BST)
- [ ] Priority Queue
- [ ] Memory Pool (Supporting)
- [ ] Ordered Map (BST)
  - [ ] Balanced Ordered Map (Red Black Tree)
  - [ ] Multi map
- [ ] Unordered Map (Hash Map)
  - [ ] Multi map

## Misc

- [ ] Figure out how to have the typed macro-defined functions be in-lined.
