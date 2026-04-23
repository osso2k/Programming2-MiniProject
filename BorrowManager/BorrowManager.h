#pragma once
#include "../Book/Book.h"
#include "../Library/Library.h"
#include <string>

class BorrowManager {
private:
  Library &library;

public:
  BorrowManager(Library &library);
  bool borrowBook(const std::string &name, const std::string &author);
  bool returnBook(const std::string &name, const std::string &author);
};
