#include "./../inc/cvol.hpp"
#include "./../inc/slider.hpp"

#include <string>

namespace raylib {
#include <raylib.h>
}

void initProgram(int width, int height, bool log) {

  if (!log) {
    raylib::SetTraceLogLevel(raylib::LOG_NONE);
  }

  raylib::SetConfigFlags(raylib::FLAG_WINDOW_TRANSPARENT);
  raylib::SetConfigFlags(raylib::FLAG_WINDOW_RESIZABLE);
  raylib::SetWindowState(raylib::FLAG_WINDOW_UNDECORATED);
  raylib::SetTargetFPS(60);

  raylib::InitWindow(width, height, "Hello World!");
}

int main() {
  constexpr int SCREEN_WIDTH = 700, SCREEN_HEIGHT = 400;

  volumeController vc;
  slider s(vc.getVolume(), [&vc](int val) { vc.setVolume(val); });
  initProgram(SCREEN_WIDTH, SCREEN_HEIGHT, false);

  const raylib::Font font = raylib::LoadFont(
      (std::string(raylib::GetApplicationDirectory()) +
       std::string("../assets/BitstromWeraNerdFont-Regular.ttf"))
          .c_str());

  while (!raylib::WindowShouldClose()) {
    raylib::BeginDrawing();
    raylib::ClearBackground(raylib::WHITE);

    DrawTextEx(font,
               ("Volume: " + std::to_string(vc.getVolume()) + "%").c_str(),
               (raylib::Vector2){20.0f, 350.0f}, (float)font.baseSize, 2,
               raylib::BLACK);

    s.render({100.0f, 100.0f, 500.0f, 80.0f}, 0.2f, raylib::DARKBLUE,
             raylib::GRAY, raylib::BLACK, raylib::BLACK, raylib::DARKGRAY,
             raylib::LIGHTGRAY);

    raylib::EndDrawing();
  }

  raylib::UnloadFont(font);
  raylib::CloseWindow();
  return 0;
}
