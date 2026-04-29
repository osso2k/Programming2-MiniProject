# CENG110 – Programming and Computation II
## Project 2 – Library Book Tracking System
### Technical Report

---

## Abstract

This report presents a modular console-based Library Book Tracking System implemented using Abstract Data Types (ADTs). The system provides complete book management including addition, removal, searching, borrowing, and returning operations. The implementation demonstrates strong encapsulation principles, modular architecture using separate ADTs, and utilizes the List data structure (std::vector) for efficient book storage. This report details the ADT design choices, data structure justification, algorithmic complexity analysis, testing methodology, and provides operational guidance for the system.

---

## 1. Introduction

### 1.1 Project Purpose

The primary objective of this project is to develop a modular software system to manage book borrowing and returns in a library setting. The system must be implemented as a console-based application using Abstract Data Types (ADTs) with proper encapsulation, hiding internal representations from external access.

### 1.2 System Overview

The Library Book Tracking System consists of three core ADTs working in coordination:

- **Book ADT**: Represents individual books with all their attributes
- **Library ADT**: Manages the collection of books and operations on the collection
- **BorrowManager ADT**: Handles the borrowing and returning workflow

The system provides a menu-driven interface with eight operations: Add Book, Remove Book, Search Book, Borrow Book, Return Book, Show All Books, Sort Books by Name, and Exit.

---

## 2. ADT Design & Encapsulation

### 2.1 Design Principles Applied

The system adheres to fundamental Object-Oriented Programming principles:

1. **Encapsulation**: All data members are private; external access only through public getters/setters
2. **Information Hiding**: Internal representations are completely hidden from users
3. **Modularity**: Each ADT is self-contained in its own module with clear responsibilities
4. **Abstraction**: Users interact only through well-defined public interfaces

### 2.2 Book ADT Design

**Location**: `Book/Book.h` and `Book/Book.cpp`

The Book ADT encapsulates all properties of a book:

```cpp
class Book {
private:
  std::string name;
  std::string author;
  std::string genre;
  int pages;
  bool available;

public:
  // Constructors and public interface
  bool isValid() const;
  // Getters and setters...
};
```

**Encapsulation Features**:
- All five data members (`name`, `author`, `genre`, `pages`, `available`) are **private**
- No direct access to internal data - all access through **public getters and setters**
- The `isValid()` method provides encapsulated validation logic
- Validation in setters prevents invalid state (e.g., empty strings, non-positive page counts)

**Strengths**:
- Complete data hiding: external code cannot directly modify `available` status
- Validation logic embedded in setters ensures data integrity
- Const-correctness: getters marked `const` indicate no state modification

### 2.3 Library ADT Design

**Location**: `Library/Library.h` and `Library/Library.cpp`

The Library ADT manages the book collection:

```cpp
class Library {
private:
  std::vector<Book> books;
  bool is_open = true;

public:
  bool addBook(const Book &book);
  bool removeBook(const std::string &name, const std::string &author);
  Book *searchBook(const std::string &name, const std::string &author);
  void sortByName();
  void showAllBooks() const;
};
```

**Encapsulation Features**:
- The internal container `std::vector<Book> books` is **private**
- External code cannot access or modify the internal collection directly
- All operations return results without exposing internal structure
- `searchBook` returns pointer (not reference) to indicate possible null state

**Modularity Strengths**:
- Single responsibility: library only manages book storage and retrieval
- Clear interface: six public methods for specific operations
- No knowledge of borrowing logic (delegated to BorrowManager)

### 2.4 BorrowManager ADT Design

**Location**: `BorrowManager/BorrowManager.h` and `BorrowManager/BorrowManager.cpp`

The BorrowManager ADT handles borrowing/returning workflow:

```cpp
class BorrowManager {
private:
  Library &library;

public:
  BorrowManager(Library &library);
  bool borrowBook(const std::string &name, const std::string &author);
  bool returnBook(const std::string &name, const std::string &author);
};
```

**Modularity Strengths**:
- **Separation of Concerns**: BorrowManager is separate from Library - different responsibility
- **Dependency Injection**: Library reference passed in constructor (not created internally)
- **Minimal Interface**: Only two public methods for clear purpose
- **State Management**: Controls availability state transitions through Library's search

### 2.5 Modular Architecture Summary

The three ADTs work together through well-defined interfaces:

```
┌─────────────────────────────────────────────────┐
│                   main.cpp                       │
│              (Menu Interface)                   │
└─────────────────────┬───────────────────────────┘
                      │
        ┌─────────────┴─────────────┐
        ▼                           ▼
┌───────────────┐           ┌───────────────┐
│BorrowManager │           │  Library    │
│  ADT        │──────────▶│  ADT        │
└─────────────┘           └──────┬──────┘
                                  │
                         ┌────────┴────────┐
                         ▼                 ▼
                    ┌─────────┐      ┌─────────┐
                    │  Book   │      │  Book   │
                    │  ADT    │      │  ADT    │
                    └─────────┘      └─────────┘
```

Each module:
- Has a single, well-defined purpose
- Exposes a minimal, coherent public interface
- Hides implementation details completely
- Can be tested independently

---

## 3. Data Structure Justification

### 3.1 Chosen Data Structure: List (std::vector)

The Library ADT uses `std::vector<Book>` — a List-based data structure.

### 3.2 Justification

**Why List over Stack or Queue?**

| Criterion | List (vector) | Stack | Queue |
|-----------|-------------|-------|-------|
| Random Access | O(1) | O(n) | O(n) |
| Search Required | Yes | No | No |
| Order Preservation | Flexible | LIFO | FIFO |
| Insertion at End | O(1) amortized | O(1) | O(1)* |
| Memory Overhead | Low | Low | Low |

**Reasons for Choosing List**:

1. **Search Requirement**: The system requires searching books by name and author (not just LIFO/FIFO access). Lists support linear search natively.

2. **Dynamic Sizing**: Library collections grow/shrink as books are added/removed. `std::vector` provides amortized O(1) push_back.

3. **Random Access**: For sorting operations and position-based access, vector provides O(1) indexed access.

4. **Cache Locality**: Vector stores elements contiguously in memory, providing better cache performance than node-based structures.

5. **Typical Library Size**: For typical library sizes (<10,000 books), vector's cache benefits outweigh any rehashing costs.

**Trade-offs Acknowledged**:
- Insertion at arbitrary positions: O(n) due to shifting
- However, our add operation appends at end; only removal requires search + erase: O(n)

---

## 4. Algorithmic Analysis (Big-O)

### 4.1 Add Book Operation

```cpp
bool Library::addBook(const Book &book) {
  if (!book.isValid()) { return false; }
  for (auto &b : books) {              // O(n) linear scan
    if (book.getName() == b.getName() && book.getAuthor() == b.getAuthor()) {
      return false;                     // Duplicate found
    }
  }
  books.push_back(book);               // O(1) amortized
  return true;
}
```

**Complexity: O(n)**

**Reasoning**: Must scan all existing books to check for duplicates before adding. In the worst case (no duplicates), examines all n books, then performs O(1) push_back.

---

### 4.2 Remove Book Operation

```cpp
bool Library::removeBook(const std::string &name, const std::string &author) {
  for (auto it = books.begin(); it != books.end(); ++it) {  // O(n) search
    if (it->getName() == name && it->getAuthor() == author) {
      books.erase(it);                                   // O(n) shift
      return true;
    }
  }
  return false;
}
```

**Complexity: O(n)**

**Reasoning**: Must linearly search to find the book (O(n)). The erase operation requires shifting elements (O(n)) but dominated by search complexity.

---

### 4.3 Search Book Operation

```cpp
Book *Library::searchBook(const std::string &name, const std::string &author) {
  auto it = std::find_if(books.begin(), books.end(), [&](const Book &b) {
    return b.getName() == name && b.getAuthor() == author;
  });
  // ...
}
```

**Complexity: O(n)**

**Reasoning**: Linear search through the vector using std::find_if. In worst case (book not found or is last element), examines all n books.

---

### 4.4 Sort By Name Operation

```cpp
void Library::sortByName() {
  std::sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
    return a.getName() < b.getName();
  });
}
```

**Complexity: O(n log n)**

**Reasoning**: Uses C++ std::sort which implements Introsort (hybrid of quicksort, heapsort, and insertion sort). Introsort guarantees O(n log n) worst-case complexity.

---

### 4.5 Summary Table

| Operation | Complexity | Dominant Factor |
|-----------|------------|----------------|
| addBook | O(n) | Linear duplicate check |
| removeBook | O(n) | Linear search + erase |
| searchBook | O(n) | Linear search |
| sortByName | O(n log n) | Introsort algorithm |

---

## 5. Testing & Results

### 5.1 Test Cases Implemented

The test suite includes five comprehensive test cases covering various scenarios:

#### Test 1: test_add_book (Normal Case)
- Creates a Book with valid attributes
- Adds to Library
- Verifies addition was successful
- Verifies book can be found via search

#### Test 2: test_duplicate_book (Duplicate Case)
- Creates two identical books (same name and author)
- Verifies first add succeeds
- Verifies second add correctly rejected (prevents duplicates)

#### Test 3: test_remove_book (Normal/Edge Case)
- Adds a book, then removes it
- Verifies removal returns true
- Verifies book no longer found (empty library edge case preparation)

#### Test 4: test_borrow_book (Normal Case)
- Adds a book and borrows it
- Verifies borrow returns true
- Verifies book availability changed to false

#### Test 5: test_return_book (Normal Case)
- Adds a book, borrows it, then returns it
- Verifies return succeeds
- Verifies availability restored to true

### 5.2 Test Execution Output

```
test_add_book passed
test_duplicate_book passed
test_remove_book passed
test_borrow_book passed
test_return_book passed

All tests passed successfully!
```

### 5.3 Coverage Analysis

| Category | Test Cases Covered |
|----------|-------------------|
| Normal Cases | test_add_book, test_borrow_book, test_return_book |
| Edge Cases | test_remove_book (post-removal state) |
| Invalid Input | N/A (handled in validation methods) |
| Duplicate Records | test_duplicate_book |

**Note**: Invalid input handling is validated through the `Book::isValid()` method and setter validation, which return false for invalid data (e.g., empty strings, non-positive page counts). These are implicitly tested through the addBook operation's validation check.

---

## 6. main.cpp Operational Guide

### 6.1 Compilation Instructions

From the project root directory:

```bash
# Using clang++
clang++ -std=c++23 -o run main.cpp Book/Book.cpp Library/Library.cpp BorrowManager/BorrowManager.cpp

# Using g++
g++ -std=c++23 -o run main.cpp Book/Book.cpp Library/Library.cpp BorrowManager/BorrowManager.cpp
```

### 6.2 Running the Program

```bash
./run
```

### 6.3 Menu Interface

The program presents a menu-driven interface with eight options:

```
Welcome to Our Library System!
1-Add a book
2-Remove a book
3-Search for a book
4-Borrow a book
5-Return a book
6-Show all books
7-Sort books by name
8-Exit
```

### 6.4 Sample Usage Walkthrough

**Adding a Book**:
```
Enter choice: 1
Name: Harry Potter
Author: J.K. Rowling
Genre: Fantasy
Pages: 500
Book added!
```

**Searching for a Book**:
```
Enter choice: 3
Book name: Harry Potter
Author: J.K. Rowling
Harry Potter by J.K. Rowling
```

**Borrowing a Book**:
```
Enter choice: 4
Book name: Harry Potter
Author: J.K. Rowling
Book borrowed!
```

**Returning a Book**:
```
Enter choice: 5
Book name: Harry Potter
Author: J.K. Rowling
Book returned!
```

**Sorting Books**:
```
Enter choice: 7
Books sorted!
```

**Viewing All Books**:
```
Enter choice: 6
Harry Potter by J.K. Rowling
The Hobbit by J.R.R. Tolkien
```

---

## 7. Code Organization & Modularity

### 7.1 Project Structure

```
.
├── main.cpp                    # Entry point with menu interface
├── Book/
│   ├── Book.h                 # Book ADT header
│   └── Book.cpp              # Book ADT implementation
├── Library/
│   ├── Library.h             # Library ADT header
│   └── Library.cpp          # Library ADT implementation
├── BorrowManager/
│   ├── BorrowManager.h     # BorrowManager ADT header
│   └── BorrowManager.cpp   # BorrowManager ADT implementation
└── test/
    └── test_cases.cpp       # Test suite
```

### 7.2 Modularity Strengths

1. **Separate Compilation**: Each ADT in its own module - changes to one don't require recompiling others (with proper headers)

2. **Clear Division of Responsibility**:
   - Book: Data representation only
   - Library: Collection management
   - BorrowManager: Workflow/transactions

3. **Testability**: Each ADT can be independently tested (demonstrated by test suite)

4. **Maintainability**: Bugs can be localized to specific modules

---

## 8. Conclusion

This Library Book Tracking System successfully demonstrates:

- **ADT Design**: Three well-defined ADTs with clear responsibilities and minimal interfaces
- **Encapsulation**: Complete data hiding through private members and controlled access
- **Modularity**: Separate modules with independent compilation and clear dependencies
- **Functionality**: Complete CRUD operations for books plus borrowing/returning workflow
- **Testing**: Comprehensive test suite with all tests passing

The implementation satisfies all mandatory requirements: add/remove/search/borrow/return/sort operations, List data structure usage, Big-O analysis provided, and modular design with proper encapsulation.

---

## References

1. C++ Standard Library Documentation - std::vector
2. CENG110 Project 2 Specification - Library Book Tracking System

---

*Report generated for CENG110 – Programming and Computation II*