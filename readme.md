<p align="center">
  <img src="https://blog2.novaeg.net/wp-content/uploads/2024/07/iti_logo.5b9a0fd125be.png" alt="ITI Logo" width="480" />
</p>

<h1 align="center">Users Stack Management System (Console Application)</h1>

<p align="center">
  <strong>Information Technology Institute (ITI)</strong> • <em>Object-Oriented Programming (OOP) — Lab 7</em>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-11%2F14-00599C?logo=c%2B%2B" alt="C++" />
  <img src="https://img.shields.io/badge/Windows-Linux-orange?logo=windows" alt="Windows" />
  <img src="https://img.shields.io/badge/GCC%2FMinGW-Compiler-green?logo=gnu" alt="GCC" />
  <img src="https://img.shields.io/badge/ITI-Open%20Source_Track-red" alt="ITI" />
</p>

---

## Project Overview

This project is developed as part of the **Object-Oriented Programming (OOP) track at the Information Technology Institute (ITI)**.

It is an interactive, menu-driven C++ console application that manages user records dynamically using a custom **Stack (LIFO — Last In, First Out)** data structure. The project demonstrates core OOP principles, manual dynamic memory management (deep copying, dynamic arrays, rule of three), input validation, and customized console UI rendering with the Windows API.

---

## Key Features

- **Custom Dynamic Stack Implementation**:
  - Implements dynamic resizing capability, copy constructors, assignment operator overload (deep copy), and destructor deallocation to prevent memory leaks.
- **User Data Validation & Encapsulation**:
  - Validates full user profiles: names (alphabetic check), passwords (length constraints), emails (structure validation), and age limits.
- **Interactive Terminal UI**:
  - Arrow-key navigable menu with highlighted cursor selections, color formatting, and clear screen transitions.
- **Graceful Flow Control**:
  - Allows canceling or escaping operations cleanly via the `Esc` key at any stage.

---

## Technologies & Tools

- **Language:** C++ (C++11/C++14 standard)
- **Data Structures & Concepts:** OOP, Dynamic Memory Allocation (`new`/`delete`), Custom Stack (LIFO), Deep Copy, Operator Overloading
- **System API:** Windows Console API (`windows.h`, `conio.h` for cursor navigation, text colors, and non-blocking key capture)
- **Environment:** Visual Studio Code & MinGW / GCC

---

## Project Structure

```text
Lab7/
│── include/
│   ├── console.h         # Terminal positioning, screen clearing, and color formatting
│   ├── dynamicUsers.h    # User entity definition, encapsulation, and validations
│   ├── menu.h            # Main menu navigation and interactive view screens
│   ├── stack.h           # Stack implementation with dynamic array management
│   └── utils.h           # String and input utility helper functions
│── src/
│   ├── main.cpp          # Application entry point
│   └── main.exe          # Compiled binary executable
└── readme.md             # Project documentation
```

---

## Getting Started

### Prerequisites
- A Windows environment.
- A C++ compiler (such as **MinGW / GCC**) or **Visual Studio / VS Code**.

### Build & Run

1. Open your terminal in the project directory:
   ```cmd
   cd "d:\ITI\7- (OOP)\Lab\Lab7"
   ```

2. Compile with `g++`:
   ```cmd
   g++ -std=c++11 -Iinclude src/main.cpp -o src/main.exe
   ```

3. Run the executable:
   ```cmd
   .\src\main.exe
   ```
