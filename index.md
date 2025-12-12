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
