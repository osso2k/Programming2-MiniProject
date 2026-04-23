#pragma once
#include "../Book/Book.h"
#include <string>
#include <vector>
class Library {
private:
  std::vector<Book> books;
  bool is_open = true;

public:
  bool isLibraryOpen() const;

  bool addBook(const Book &book);
  bool removeBook(const std::string &name, const std::string &author);

  Book *searchBook(const std::string &name, const std::string &author);
  void sortByName();
  void showAllBooks() const;
};
