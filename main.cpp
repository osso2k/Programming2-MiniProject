#include "Book/Book.h"
#include "Library/Library.h"
#include <iostream>

int main() {
  Library my_lib;
  Book p1("Harry Potter", "Just Kidding Rolling", "fantasy", 9999);
  Book p2("A Song of Ice and Fire ", "Martin R.R", "fantasy", 1000);
  std::cout << p1.getAuthor() << '\n';
  p1.setAuthor("J.K Rolling");
  std::cout << p1.getAuthor() << '\n';
  my_lib.addBook(p1);
  my_lib.addBook(p2);
  Book *my_book = my_lib.searchBook("Harry Potter", "J.K Rolling");
}
