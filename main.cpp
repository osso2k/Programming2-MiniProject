#include "Book/Book.h"
#include "BorrowManager/BorrowManager.h"
#include "Library/Library.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
  Library my_lib;
  BorrowManager manager(my_lib);

  std::cout << "Welcome to Our Library System!\n";

  std::vector<std::string> options = {
      "1-Add a book",         "2-Remove a book", "3-Search for a book",
      "4-Borrow a book",      "5-Return a book", "6-Show all books",
      "7-Sort books by name", "8-Exit"};

  bool active = true;

  while (active) {
    for (const auto &opt : options) {
      std::cout << opt << "\n";
    }

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
      std::string name, author, genre;
      int pages;

      std::cout << "Name: ";
      std::getline(std::cin, name);

      std::cout << "Author: ";
      std::getline(std::cin, author);

      std::cout << "Genre: ";
      std::getline(std::cin, genre);

      std::cout << "Pages: ";
      std::cin >> pages;
      std::cin.ignore();

      Book book(name, author, genre, pages);

      if (my_lib.addBook(book)) {
        std::cout << "Book added!\n";
      } else {
        std::cout << "Couldn't add book.\n";
      }
    }

    else if (choice == 2) {
      std::string name, author;

      std::cout << "Book name: ";
      std::getline(std::cin, name);

      std::cout << "Author: ";
      std::getline(std::cin, author);

      if (my_lib.removeBook(name, author)) {
        std::cout << "Book removed!\n";
      } else {
        std::cout << "Couldn't remove book.\n";
      }
    }

    else if (choice == 3) {
      std::string name, author;

      std::cout << "Book name: ";
      std::getline(std::cin, name);

      std::cout << "Author: ";
      std::getline(std::cin, author);

      Book *book = my_lib.searchBook(name, author);

      if (book) {
        std::cout << book->getName() << " by " << book->getAuthor() << "\n";
      } else {
        std::cout << "Couldn't find book.\n";
      }
    }

    else if (choice == 4) {
      std::string name, author;

      std::cout << "Book name: ";
      std::getline(std::cin, name);

      std::cout << "Author: ";
      std::getline(std::cin, author);

      if (manager.borrowBook(name, author)) {
        std::cout << "Book borrowed!\n";
      } else {
        std::cout << "Couldn't borrow book.\n";
      }
    }

    else if (choice == 5) {
      std::string name, author;

      std::cout << "Book name: ";
      std::getline(std::cin, name);

      std::cout << "Author: ";
      std::getline(std::cin, author);

      if (manager.returnBook(name, author)) {
        std::cout << "Book returned!\n";
      } else {
        std::cout << "Couldn't return book.\n";
      }
    }

    else if (choice == 6) {
      my_lib.showAllBooks();
    }

    else if (choice == 7) {
      my_lib.sortByName();
      std::cout << "Books sorted!\n";
    }

    else if (choice == 8) {
      active = false;
      std::cout << "Thanks for stopping by!\n";
    }
  }

  return 0;
}
