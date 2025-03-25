# CPU_Design
# Overview

This project is a functional model of a basic CPU, developed in C++ in collaboration with two partners. The design integrates key components such as the Arithmetic Logic Unit (ALU), Control Unit, Register File, and instruction parsing. Through this hands-on experience, we explored low-level system design and hardware architecture.

# Key Components and Features

# ALU (Arithmetic Logic Unit)

Supports operations including addition, subtraction, logical operations (AND, OR, XOR), multiplication, division, and comparisons (SLT, SGT, SEQ).

Implements overflow detection to handle both positive and negative overflow cases.

# Control Unit

Decodes opcodes and manages control signals.

Enables memory access, jumps, branches, and ALU operation selection.

Works in tandem with the ALU to execute instructions based on opcode and function codes.

# Register File

Supports reading and writing to registers.

Ensures correct data flow and manipulation during instruction execution.

Instruction Parsing

Converts assembly instructions into binary for execution.

Processes opcode, registers, and immediate values for proper instruction execution.

# Tools and Libraries

C++: Used to develop the core CPU model and handle logic and functionality.

Bitset (C++ Standard Library): Used for binary conversion and manipulation of instructions and operands.

Overflow Detection Logic: Prevents errors during arithmetic operations by detecting overflow conditions.

# Learning Outcomes

This project enhanced our understanding of computer architecture, system-level programming, and hardware design. By building a functional CPU model, we gained hands-on experience in how hardware components interact and refined our skills in low-level programming.

# How to Run

Clone this repository.

Compile the C++ source code using a compatible compiler (e.g., g++).

Execute the compiled program to simulate CPU operations.

# Future Enhancements

Implement pipelining for instruction execution.

Expand the instruction set for more complex operations.

Optimize memory access and register management for better efficiency.

