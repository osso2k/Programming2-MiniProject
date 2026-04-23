#include "BorrowManager.h"
#include "../Book/Book.h"
#include "../Library/Library.h"
#include <string>

BorrowManager::BorrowManager(Library &library) : library(library) {}
bool BorrowManager::borrowBook(const std::string &name,
                               const std::string &author) {
  Book *book = library.searchBook(name, author);
  if (!book || book->isAvailable() == false) {
    return false;
  }
  book->setAvailable(false);
  return true;
}
bool BorrowManager::returnBook(const std::string &name,
                               const std::string &author) {
  Book *book = library.searchBook(name, author);
  if (!book || book->isAvailable()) {
    return false;
  }
  book->setAvailable(true);
  return true;
}
