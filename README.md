# Assignment 2 - Operating Systems

## Overview
This project involves implementing a simple memory management system in C. The primary focus is on creating dynamic memory allocation and deallocation functions: 

- `simple_malloc`: Allocates memory blocks dynamically with 8-byte alignment.
- `simple_free`: Frees up previously allocated memory blocks to avoid memory leaks.

The memory manager employs a next-fit allocation strategy using a circular singly-linked list of memory blocks.

## Features
- **Custom Memory Allocation**: Implements `simple_malloc` for dynamic memory allocation with proper alignment for improved performance on most systems.
- **Custom Memory Deallocation**: Implements `simple_free` to release allocated memory and prevent memory leaks.
- **Next-Fit Allocation Strategy**: Uses a next-fit algorithm to efficiently allocate memory within a continuous memory region.
- **Unit Testing**: Provides unit tests using the `check` library to verify the correct functioning of the custom memory manager.

## Setup and Usage

1. **Environment Setup**: Make sure you are working in a Unix or POSIX-compliant environment (Linux or macOS). You will also need to install the `check` library for running tests.
   
2. **Building the Program**: Use the provided `Makefile` to compile the project. Run the following command to build both the test suite and the main application:
   `make`

3. Running Unit Tests: After building, run the memory management unit tests with:
`make malloc_check`

4. Running the Main Program: Run the program that integrates the custom memory manager with the command interpreter from Assignment 1:
`make cmd_int`


## Project Files
**mm.h**: Prototypes and definitions for memory management.
- **mm.c**: Implementation of `simple_malloc` and `simple_free`.
- **check_mm.c**: Contains unit tests for the memory manager.
- **Makefile**: Builds both the test and the main application executables.
- **main.c**: Contains the main logic and integration of the memory manager.
- **io.c / io.h**: Input/output management used in the project.
- **memory_setup.c**: Additional memory setup functions.
- **mm_aux.c**: Auxiliary memory management functions.
- **test.sh**: Shell script for testing the project.
- **test_mm.c**: Contains additional test cases for memory management.
- **CMakeLists.txt**: CMake configuration file.
- **CircularSinglyLinkedList.puml**: UML diagram of the circular singly-linked list structure used in memory management.


## Authors
**Group 32:**
- Setare Izadi - s232629
- Aisha Farah - s235123
- Sarah Dimovski - s235087
- Kasparas Marcinskas - s235116
