// Copyright 2019, Cristián Donoso.
// This code has a BSD license. See LICENSE.

#include <thread>

#include <rothko/utils/logging.h>
#include <rothko/window/window.h>

using namespace rothko;

int main() {
  Window window = {};
  InitWindowConfig window_config = {};
  window_config.type = WindowType::kSDLOpenGL;
  if (!InitWindow(&window, &window_config)) {
    LOG(ERROR, "Could not initialize window. Exiting.");
    return 1;
  }

  Input input = {};

  // Sample game loop.
  bool running = true;
  while (running) {
    auto events = NewFrame(&window, &input);
    for (auto event : events) {
      if (event == WindowEvent::kQuit) {
        running = false;
        break;
      }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
}
