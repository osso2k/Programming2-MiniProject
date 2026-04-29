#include "../Book/Book.h"
#include "../BorrowManager/BorrowManager.h"
#include "../Library/Library.h"
#include <cassert>
#include <iostream>

void test_add_book() {
  Library lib;

  Book b("Harry Potter", "J K Rowling", "Fantasy", 500);

  bool added = lib.addBook(b);

  assert(added == true);

  Book *found = lib.searchBook("Harry Potter", "J K Rowling");
  assert(found != nullptr);

  std::cout << "test_add_book passed\n";
}

void test_duplicate_book() {
  Library lib;

  Book b1("Book", "Author", "Genre", 100);
  Book b2("Book", "Author", "Genre", 100);

  assert(lib.addBook(b1) == true);
  assert(lib.addBook(b2) == false); // duplicate

  std::cout << "test_duplicate_book passed\n";
}

void test_remove_book() {
  Library lib;

  Book b("Book", "Author", "Genre", 100);
  lib.addBook(b);

  bool removed = lib.removeBook("Book", "Author");

  assert(removed == true);
  assert(lib.searchBook("Book", "Author") == nullptr);

  std::cout << "test_remove_book passed\n";
}

void test_borrow_book() {
  Library lib;
  BorrowManager manager(lib);

  Book b("Book", "Author", "Genre", 100);
  lib.addBook(b);

  bool borrowed = manager.borrowBook("Book", "Author");

  assert(borrowed == true);

  Book *found = lib.searchBook("Book", "Author");
  assert(found->isAvailable() == false);

  std::cout << "test_borrow_book passed\n";
}

void test_return_book() {
  Library lib;
  BorrowManager manager(lib);

  Book b("Book", "Author", "Genre", 100);
  lib.addBook(b);

  manager.borrowBook("Book", "Author");
  bool returned = manager.returnBook("Book", "Author");

  assert(returned == true);

  Book *found = lib.searchBook("Book", "Author");
  assert(found->isAvailable() == true);

  std::cout << "test_return_book passed\n";
}

int main() {
  test_add_book();
  test_duplicate_book();
  test_remove_book();
  test_borrow_book();
  test_return_book();

  std::cout << "\nAll tests passed successfully!\n";
  return 0;
}
