#include "Book.h"
#include <string>

Book::Book(const std::string &name, const std::string &author,
           const std::string &genre, int pages)
    : name(name), author(author), genre(genre), pages(pages), available(true) {}
bool Book::setName(const std::string &new_name) {
  if (new_name.empty())
    return false;
  name = new_name;
  return true;
}
bool Book::setAuthor(const std::string &new_author) {
  if (new_author.empty())
    return false;
  author = new_author;
  return true;
}
bool Book::setGenre(const std::string &new_genre) {
  if (new_genre.empty())
    return false;
  genre = new_genre;
  return true;
}
bool Book::setPages(int new_pages) {
  if (!new_pages || new_pages <= 0)
    return false;
  pages = new_pages;
  return true;
}
bool Book::setAvailable(bool available) {
  this->available = available;
  return true;
}
bool Book::isValid() const {
  if (name.empty() || author.empty()) {
    return false;
  } else {
    return true;
  }
}
std::string Book::getName() const { return name; }
std::string Book::getAuthor() const { return author; }
std::string Book::getGenre() const { return genre; }
int Book::getPages() const { return pages; }
bool Book::isAvailable() const { return available; }
