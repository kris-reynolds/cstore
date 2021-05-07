# cstore

[![CI](https://github.com/kris-reynolds/cstore/actions/workflows/test.yml/badge.svg)](https://github.com/kris-reynolds/cstore/actions/workflows/test.yml)

Container library for C.

`cstore` provides various common container implementations in C.  In order to cater to the typical C use case (embedded devices) the developer can provide their own memory buffer, or allow the library to manage the memory for them.

Through macros "type safe" container accessors/modifiers can be generated.  However they currently come at the cost of an extra re-direct.

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

- [ ] Array
- [ ] Vector
- [ ] Queue
- [ ] Stack
- [ ] Single Linked List
- [ ] Double Linked List
- [ ] Set
- [ ] Priority Queue
- [ ] Ordered Map (BST)
  - [ ] Balanced Ordered Map (Red Black Tree)
  - [ ] Multi map
- [ ] Unordered Map (Hash Map)
  - [ ] Multi map

## Misc

- [ ] Figure out how to have the typed macro-defined functions be in-lined.
