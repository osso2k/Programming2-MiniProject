# Library Book Tracking System

A modular console-based system to manage book borrowing and returns, implemented using Abstract Data Types (ADTs).

## Features

- **Book Management**: Add, remove, and search for books
- **Borrowing System**: Borrow and return books with availability tracking
- **Sorting**: Sort books by name

## ADT Design

### Book ADT
Represents a book with properties:
- Name (string)
- Author (string)
- Genre (string)
- Pages (int)
- Available (bool)

Encapsulation: All data members are private with public getters/setters.

### Library ADT
Manages a collection of books using `std::vector` (List data structure).

### BorrowManager ADT
Handles borrowing and returning operations, manages book availability.

## Data Structure Justification

Using `std::vector` (List) because:
- Supports O(1) random access
- Dynamic resizing for flexible book collection
- Cache-friendly memory layout
- Suitable for typical library sizes (< 10,000 books)

## Time Complexity

| Operation | Complexity | Reasoning |
|-----------|------------|-----------|
| addBook   | O(n)       | Linear search for duplicates |
| removeBook| O(n)       | Linear search to find book |
| searchBook| O(n)       | Linear search through list |
| sortByName| O(n log n) | Uses std::sort (introsort) |

## Building

### Compile

```bash
clang++ -std=c++23 -o run main.cpp Book/Book.cpp Library/Library.cpp BorrowManager/BorrowManager.cpp
 or
g++ -o run main.cpp Book/Book.cpp Library/Library.cpp BorrowManager/BorrowManager.cpp
```

### Run Tests

```bash
clang++ -std=c++23 -o test test/test_cases.cpp Book/Book.cpp Library/Library.cpp BorrowManager/BorrowManager.cpp ./test
```

### Execute

```bash
./run
```

## Project Structure

```
.
├── main.cpp                    # Main entry point with menu interface
├── Book/
│   ├── Book.h                 # Book ADT
│   └── Book.cpp               # Book implementation
├── Library/
│   ├── Library.h              # Library ADT
│   └── Library.cpp           # Library implementation
├── BorrowManager/
│   ├── BorrowManager.h        # BorrowManager ADT
│   └── BorrowManager.cpp     # BorrowManager implementation
└── test/
    └── test_cases.cpp         # Test cases
```

## Usage

The program provides a menu-driven interface:
1. Add a book
2. Remove a book
3. Search for a book
4. Borrow a book
5. Return a book
6. Show all books
7. Sort books by name
8. Exit
