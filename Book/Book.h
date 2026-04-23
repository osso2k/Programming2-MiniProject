#pragma once
#include <string>
class Book {
private:
  std::string name;
  std::string author;
  std::string genre;
  int pages;
  bool available;

public:
  Book(const std::string &name, const std::string &author,
       const std::string &genre, int pages);
  bool setName(const std::string &name);
  bool setAuthor(const std::string &author);
  bool setGenre(const std::string &genre);
  bool setPages(int pages);
  bool setAvailable(bool available);
  bool isValid() const;
  std::string getName() const;
  std::string getAuthor() const;
  std::string getGenre() const;
  int getPages() const;
  bool isAvailable() const;
};
