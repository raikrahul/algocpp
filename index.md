# Algorithm C++ Workspace

C++ workspace for algorithm implementations and problem-solving.

## Structure

- **C++ Files**: Algorithm implementations
- **Markdown Files**: Problem descriptions, derivations, notes
- **Build System**: CMake

## Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake ..

# Build all
cmake --build .

# Build specific target
cmake --build . --target <executable_name>
```

## Run Instructions

```bash
# From build directory
./bin/<executable_name>

# Or from root
./build/bin/<executable_name>
```

## Problems

1. [Spell Checker](01_spell_checker.md) - [Code](01_spell_checker.cpp)
2. [Bidirectional Symbol Table](02_bidirectional_symbol_table.md) - [Code](02_bidirectional_symbol_table.cpp)
3. [Inverted Index](03_inverted_index.md) - [Code](03_inverted_index.cpp)
4. [LFU Cache](04_lfu_cache.md) - [Code](04_lfu_cache.cpp)
5. [Minimum Gas Stops](05_minimum_gas_stops.md) - [Code](05_minimum_gas_stops.cpp)
6. [Minimum Sector Traversal](06_minimum_sector_traversal.md) - [Code](06_minimum_sector_traversal.cpp)
