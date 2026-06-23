#include "PlusUltra.h"
#include <iostream>

int main() {
  Vector2 a = Vector2(4, 0);
  Vector2 b = Vector2(-4, 0);
  std::cout << a.Distance(b);
  return 0;
}
