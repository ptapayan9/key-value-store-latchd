# Latch

A Redis-inspired, in-memory key-value store written in C++20.

Latch currently provides a storage library for string keys and values, with
operations to insert, update, and retrieve entries. The `latchd` executable runs
a small demonstration of the storage API.

The project is in early development. TCP access, command parsing, persistence,
and concurrent request handling are planned; the current executable does not
run a network server. Data lives in memory for the lifetime of the store.

## Features

- Insert a key-value pair or replace an existing value with `set`.
- Retrieve a value with `get`, returning `std::nullopt` when the key is missing.
- Distinguish a stored empty string from a missing key.
- Reuse the storage implementation through the `latch_store` library.
- Run automated behavior tests with Catch2 and CTest.

## Build and run

Requirements:

- A C++20-capable Clang or GCC compiler.
- CMake 3.20 or newer.
- Git and internet access for the first configuration with tests enabled, which
  downloads Catch2 v3.8.1.

Run from the repository root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 4
./build/latchd
```

The current demonstration stores a value, retrieves it, and then overwrites it:

```text
latch
Latch-overwrite
```

## Tests

Tests are enabled by default. After building, run:

```sh
ctest --test-dir build --output-on-failure
```

The suite covers retrieval, overwrites, missing keys, empty values, and isolation
between different keys.

To build only the application and storage library:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF
cmake --build build --parallel 4
```

Pass `-DBUILD_TESTING=ON` when configuring again to re-enable tests.
