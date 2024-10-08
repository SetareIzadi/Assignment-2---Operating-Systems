# Assignment 2 - Operating Systems

### Overview
This assignment involves implementing a basic memory management system in C, focusing on dynamic memory allocation and deallocation. The two primary functions you will implement are:

- `simple_malloc`: Dynamically allocates memory blocks.
- `simple_free`: Frees previously allocated memory blocks.

### Key Features
- **Memory Allocation**: Implements `simple_malloc`, which allocates memory dynamically and aligns allocations to 8-byte boundaries for optimal performance.
- **Memory Deallocation**: Implements `simple_free`, allowing for the efficient release of memory, reducing memory leaks.
- **Next-fit Allocation Strategy**: Utilizes a circular singly-linked list of memory blocks and a "next-fit" strategy for memory allocation.
- **Custom Unit Tests**: Includes a test framework using the `check` library to verify the correct functioning of the memory manager.
- **Replacement of Standard Malloc/Free**: Replaces the default C library memory allocation functions (`malloc` and `free`) in a previously implemented program.
