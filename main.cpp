#include "Product/Product.h"
#include <iostream>

int main() {
  Product p1("Jacket", 23, 1);
  std::cout << p1.getName() << '\n';
  p1.setName("Hat");
  std::cout << p1.getName() << '\n';
}
