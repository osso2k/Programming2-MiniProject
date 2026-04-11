#include "Product.h"
#include <string>

Product::Product(std::string name, double price, int quantity) {
  this->name = name;
  this->price = price;
  this->quantity = quantity;
}
bool Product::setName(std::string new_name) {
  name = new_name;
  return true;
}
bool Product::setPrice(double new_price) {
  price = new_price;
  return true;
}
bool Product::setQuantity(int new_quantity) {
  quantity = new_quantity;
  return true;
}
std::string Product::getName() { return name; }
double Product::getPrice() { return price; }
int Product::getQuantity() { return quantity; }
