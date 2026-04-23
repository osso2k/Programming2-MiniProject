#include "Library.h"
#include "../Book/Book.h"
#include <algorithm>
#include <iostream>
#include <string>

bool Library::isLibraryOpen() const { return is_open; }
bool Library::addBook(const Book &book) {
  if (!book.isValid()) {
    return false;
  }
  for (auto &b : books) {
    if (book.getName() == b.getName() && book.getAuthor() == b.getAuthor()) {
      return false;
    }
  }
  books.push_back(book);
  return true;
}
bool Library::removeBook(const std::string &name, const std::string &author) {
  for (auto it = books.begin(); it != books.end(); ++it) {
    if (it->getName() == name && it->getAuthor() == author) {
      books.erase(it);
      return true;
    }
  }
  return false;
}
Book *Library::searchBook(const std::string &name, const std::string &author) {
  auto it = std::find_if(books.begin(), books.end(), [&](const Book &b) {
    return b.getName() == name && b.getAuthor() == author;
  });
  if (it != books.end()) {
    return &*it;
  } else {
    return nullptr;
  }
}
void Library::sortByName() {
  std::sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
    return a.getName() < b.getName();
  });
}
void Library::showAllBooks() const {
  if (books.empty()) {
    std::cout << "No books available yet..." << "\n";
    return;
  }
  for (const auto &book : books) {
    std::cout << book.getName() << " by " << book.getAuthor() << "\n";
  }
}
