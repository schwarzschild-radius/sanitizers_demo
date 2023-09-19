// clang++ ubsan.cpp -fsanitize=undefined -g 

#include <iostream>

int main(int argc, char **argv) {
  int a, b;
  std::cin >> a >> b;
  return a / b;
}