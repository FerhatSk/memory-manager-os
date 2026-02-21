# 🧠 OS Memory Manager Emulator in C

![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Linux%20%2F%20Windows%20(WSL)-green)
![Data Structure](https://img.shields.io/badge/Data%20Structure-Doubly%20Linked%20List-orange)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

## 📖 Overview

This project is a custom **Dynamic Memory Allocator** written in C. Developed for an Operating Systems course, it simulates the low-level behavior of standard `malloc()` and `free()` functions. The system manages a static memory pool using a **Doubly Linked List** to track allocated and free blocks. 

It provides an interactive Command Line Interface (CLI) to allocate memory, free specific blocks, and visualize the real-time memory map.

## ✨ Key Features

* **⚡ First-Fit Algorithm:** Efficiently scans the memory pool to find the first block that is large enough to satisfy the allocation request.
* **✂️ Block Splitting:** Prevents internal fragmentation. If a free block is larger than requested, it automatically splits the block into two: one for the user data and one for the remaining free space.
* **🔄 Automatic Coalescing:** Eliminates external fragmentation. When memory is freed, the system checks adjacent blocks and merges them if they are also free, creating larger contiguous memory segments.
* **⏱️ Performance Benchmarking:** Uses POSIX `clock_gettime()` to measure and report allocation times in milliseconds, ensuring high-resolution performance tracking.
* **🛡️ Memory Alignment Safe:** Utilizes `__attribute__((packed))` for metadata structs, preventing hardware alignment faults commonly found in embedded systems.

## 🧱 Architecture & Memory Map

The memory pool is divided into blocks. Each block consists of a **Metadata Header** (containing size, status, and list pointers) followed by the actual **User Data**.

| Metadata (Block struct) | User Data | Metadata | User Data | ... |
| :---: | :---: | :---: | :---: | :---: |
| 24 Bytes | *Variable Size* | 24 Bytes | *Variable Size* | ... |

## 📸 CLI Interface

The system provides a clean terminal interface to interact with the memory pool.

| Memory Map Output | Allocation Tracking |
| :--- | :--- |
| `BLOCK 0: USED, Size: 1024 | Address: 0x...` <br> `BLOCK 1: FREE, Size: 19432 | Address: 0x...` | `[0] 1024 bytes at 0x...` <br> `>> SUCCESS: Memory freed.` |

## 🛠️ Tech Stack & Requirements

* **Language:** C (C99 standard or higher)
* **Compiler:** GCC
* **Build Tool:** GNU Make
* **OS:** POSIX compliant systems (Linux, macOS, Windows via WSL)

## 🚀 Installation & Usage

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/mVefa/memory-manager-os.git](https://github.com/mVefa/memory-manager-os.git)
    cd memory-manager-os
    ```
2.  **Compile the Project:**
    ```bash
    make
    ```
3.  **Run the Emulator:**
    ```bash
    ./bellek_yoneticisi
    ```
4.  *(Optional) Clean build files:*
    ```bash
    make clean
    ```

## 🔮 Future Work (Roadmap)

* **Thread Safety:** Implementing `mutex` locks to make the allocator thread-safe for multi-threaded applications.
* **Algorithm Switcher:** Adding options to switch between *First-Fit*, *Best-Fit*, and *Worst-Fit* allocation strategies at runtime.
* **Memory Paging Simulation:** Expanding the emulator to support virtual memory paging and page replacement algorithms (LRU, FIFO).

## 👨‍💻 Author

**Muhammet Vefa Yoksul**

**Ferhat Işık**



---
*Built with ❤️ for OS enthusiasts*
