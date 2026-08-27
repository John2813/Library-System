# Library Management System

A terminal-based Library Management System implemented in C++. This project is designed as a hands-on learning exercise to deepen understanding of C++ Object-Oriented Programming (OOP), manual memory management, file persistence, and terminal UI design by building core data structures and system architecture from scratch.

---

## 📌 Project Goals & Learning Objectives

This is a **learning and practice project** focused on understanding fundamental data structures and system design without relying on high-level container abstractions. The primary objectives achieved through developing this project include:

* **Object-Oriented Programming (OOP) in C++**: Practicing class encapsulation, inheritance, and separation of responsibilities across system modules.
* **Data Structures & Memory Management**:
* Implementing custom singly linked lists (`BookNode` / `UserNode`) to manage dynamic data.
* Mastering pointer operations and edge-case handling during node updates.
* Working with C++ dynamic memory allocation (`new` / `delete`) and implementing destructors to prevent memory leaks.


* **File I/O & Data Persistence**: Utilizing `std::ifstream`, `std::ofstream`, and `std::stringstream` to perform data loading, appending, and in-place overwriting.
* **Layered Software Architecture**: Decoupling business logic (`Library`) from UI/Control flow (`LibraryUI` / `main`), adhering to the Single Responsibility Principle (SRP).
* **Terminal Interaction & TUI**: Exploring standard console I/O and integrating the `ncurses` library for terminal-based user interfaces.

---

## 🏗️ System Architecture

The project adopts a lightweight layered architecture to minimize coupling between components:

```text
+-------------------------------------------------------+
|              UI / Control Layer (main / CLI)          |
|      - Handles std::cin / std::cout & menu loops      |
+-------------------------------------------------------+
                           |
                           v
+-------------------------------------------------------+
|            Business Logic Layer (Library)             |
|      - Login, register, borrow/return, file sync      |
+-------------------------------------------------------+
             /                           \
            v                             v
+-----------------------+     +-----------------------+
|   Data Node Layer     |     |  Base Entity Layer    |
|   - BookNode          |     |  - Book               |
|   - UserNode          |     |  - User               |
+-----------------------+     +-----------------------+

```

---

## 🛠️ Tech Stack & Requirements

* **Language**: C++11 or higher
* **Compiler / Build Tools**: `GCC` / `G++`, `Make`, or `CMake`
* **Dependencies**: `ncurses` (for terminal interface integration)
* **Environment**: Linux (Fedora / Arch Linux, etc.) / VS Code

---

## ⚙️ Key Features

### 1. User Management

* **Authentication**: Support for new user registration and username/password authentication.
* **Role-Based Access Control**:
* **Standard Users**: Browse book listings, borrow/return books, and view personal borrowed records.
* **Administrator (Root)**: Inherits all standard privileges, with additional capabilities to view all registered users, delete user accounts, add new titles, and remove existing books.



### 2. Inventory & Circulation

* **Catalog Browsing**: Formatted display of available books and copy counts.
* **Borrowing & Returns**: Dynamic inventory tracking and linkage to individual user borrowing histories.

### 3. Data Persistence

* File loading from local storage (`Book_data` and `User_data`) on initialization.
* Append-only writes for new entries and state overwriting for record updates.

---

## 🚀 Build & Run

### 1. Compilation

Compile using `g++` while linking the `ncurses` library:

```bash
g++ -std=c++11 main.cpp Library.cpp Book.cpp User.cpp BookNode.cpp UserNode.cpp -o library_sys -lncurses

```

### 2. Execution

```bash
./library_sys

```

---

## 📝 Roadmap & Future Improvements (TODO)

* [ ] **Smart Pointers**: Replace raw pointers with `std::unique_ptr` and `std::shared_ptr` for automated and safer memory management.
* [ ] **STL Container Integration**: Transition custom linked list implementations to `std::vector` or `std::list` to benchmark memory overhead and code maintainability.
* [ ] **Full TUI Enhancements**: Expand `ncurses` usage for a richer terminal UI featuring multi-window navigation and highlighted menus.
