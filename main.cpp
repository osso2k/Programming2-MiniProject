#include <iostream>
#include <list>
#include <string>

class Item {
private:
  std::string name;
  double price;
  int quantity;

public:
  Item(std::string name, double price, int q) {
    this->name = name;
    this->price = price;
    this->quantity = q;
  };
};
class ShoppingCart {};

int main() {}
