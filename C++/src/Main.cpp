#include "PlusUltra.h"
#include <chrono>
#include <iostream>

void MainLoop() {
  auto LastCall = std::chrono::steady_clock::now();
  double Time = 0;
  double Delta = 0.016;
  bool Running = true;
  Vector2 a = Vector2(0, 0);
  while (Running) {
    auto now = std::chrono::steady_clock::now();

    if (now - LastCall >= std::chrono::milliseconds(int(Delta * 1000))) {
      LastCall = now;
      Time += Delta;
      a.X += Delta;
      a.Y += Delta;
      std::cout << a << "\n";
    }
  }
}

int main() {

  MainLoop();
  return 0;
}
