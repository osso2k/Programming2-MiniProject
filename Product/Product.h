#pragma once
#include <string>
class Product {
private:
  std::string name;
  double price;
  int quantity;

public:
  Product(std::string name, double price, int quantity);
  bool setName(std::string name);
  bool setPrice(double price);
  bool setQuantity(int q);
  std::string getName();
  double getPrice();
  int getQuantity();
};
