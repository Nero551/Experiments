#include "../PlusUltra.h"
#include <iostream>

Entity entity;

void Engine::Start() { entity.Velocity = {0, 5, 0}; }

void Engine::Process(double delta) {
  entity.Position += entity.Velocity * delta;
  std::cout << entity.Position << "\n";
}

void Engine::Stop() {}
