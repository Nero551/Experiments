#include "PlusUltra.h"
#include <chrono>

const double Delta = 0.016;

int main() {
  Engine engine;
  auto LastCall = std::chrono::steady_clock::now();

  engine.Running = true;
  engine.Start();
  while (engine.Running) {
    auto now = std::chrono::steady_clock::now();

    if (now - LastCall >= std::chrono::milliseconds(int(Delta * 1000))) {
      LastCall = now;
      engine.Time += Delta;
      engine.Process(Delta);
    }
  }

  engine.Stop();
  return 0;
}
