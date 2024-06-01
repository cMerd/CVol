#include <string>

#include "../inc/app.hpp"
#include "../inc/log.hpp"

namespace raylib {
#include <raylib.h>
}

app::app(int width, int height, const std::string &title,
         const raylib::Color &col, bool log_raylib) {

  this->bg = col;
  this->log = log_raylib;

  if (!this->log) {
    raylib::SetTraceLogLevel(raylib::LOG_NONE);
  }

  raylib::SetConfigFlags(
      raylib::FLAG_WINDOW_TRANSPARENT | raylib::FLAG_WINDOW_RESIZABLE |
      raylib::FLAG_WINDOW_UNDECORATED | raylib::FLAG_VSYNC_HINT);
  logln("Window flags set.");

  raylib::InitWindow(width, height, "CVol");
  logln("Window created.");
}

app::~app() {
  logln("Exitting program...");

  raylib::UnloadFont(font);
  logln("Unloaded font.");

  raylib::CloseWindow();
  logln("Window closed.");
}

bool app::shouldClose() const { return raylib::WindowShouldClose(); }

void app::clear() const {
  raylib::BeginDrawing();
  raylib::ClearBackground(bg);
}

void app::process() const {
  if (log) {
    raylib::DrawTextEx(font,
                       (std::to_string(raylib::GetFPS()) + " FPS").c_str(),
                       {10, 10}, 20, 2, fg);
  }
  raylib::EndDrawing();
}

void app::drawText(const std::string &text, float xPos, float yPos) const {
  DrawTextEx(font, text.c_str(), (raylib::Vector2){xPos, yPos}, fontSize, 2,
             fg);
}

void app::loadFont(const std::string &font_path, int font_size,
                   const raylib::Color &fg) {
  this->font = raylib::LoadFontEx(font_path.c_str(), font_size, NULL, 0);
  this->fg = fg;
  logln("Font loaded.");
}

raylib::Font app::getFont() const { return font; }
