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
7. [Merry Milk Makers](07_merry_milk_makers.md) - [Code](07_merry_milk_makers.cpp)
8. [Maximize the Tip](08_max_tip.md) - [Code](08_max_tip.cpp)
9. [Student Test strategies](09_student_test.md) - [Code](09_student_test.cpp)
10. [Recurrence DP](10_recurrence_dp.md) - [Code](10_recurrence_dp.cpp)

11. [Legal Paths](11_legal_paths.md) - [Code](11_legal_paths.cpp)
12. [Max Sum No Adjacent](12_max_sum_no_adjacent.md) - [Code](12_max_sum_no_adjacent.cpp)
13. [SuperStack O(1) Max](13_super_stack.md) - [Code](13_super_stack.cpp)
14. [Queue with Stacks](14_queue_with_stacks.md) - [Code](14_queue_with_stacks.cpp)
15. [Stock Span](15_stock_span.md) - [Code](15_stock_span.cpp)
