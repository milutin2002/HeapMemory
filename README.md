# HeapMemory — Custom Heap Memory Allocator

A low-level heap memory manager implemented in C/C++, exploring two
distinct approaches to dynamic memory allocation from scratch —
without relying on malloc or any standard allocator.

## Overview

This project implements a custom heap allocator to deeply understand
how memory management works at the OS boundary. Two allocator
strategies are implemented, each with different trade-offs in
complexity and control.

## Implementations

### 1. sbrk/brk Allocator (`/Sbrk`) — ✅ Complete

A fully functional heap allocator using the `sbrk` syscall to grow
the process data segment on demand.

**How it works:**
- Maintains a free list of memory blocks using a linked list structure
- Implements first-fit allocation strategy
- Coalesces adjacent free blocks to reduce fragmentation
- Uses `sbrk()` to request additional memory from the OS when no
  suitable free block exists
- Implements `malloc`, `free`, and `realloc` equivalents

**Key concepts demonstrated:**
- Process memory layout (heap segment)
- Free list management and block metadata
- Internal and external fragmentation handling
- Memory alignment

### 2. Virtual Memory Page Allocator (`/virtualMemory`) — 🔬 In Progress

An exploration of lower-level memory management using `mmap` to
allocate memory directly at the virtual memory page level.

**Goal:** Manage memory at page granularity, bypassing the
traditional heap entirely and interacting directly with the OS
virtual memory subsystem.

**Concepts being explored:**
- `mmap`/`munmap` for anonymous memory mapping
- Page-aligned allocation
- Virtual memory layout and address space management
- Build specific structure for every type that is registered

## Why This Project

Understanding how allocators work is foundational to systems
programming and security research. Custom allocators expose:

- How heap vulnerabilities like heap overflows, use-after-free,
  and double-free bugs arise at the implementation level
- How allocator metadata can be targeted and corrupted in
  exploitation scenarios
- The OS mechanisms (sbrk, mmap) that underpin all dynamic
  memory in user space


## Tech Stack

- C / C++
- CMake
- Linux system calls (sbrk, mmap)
- Linked list block management
