#include "../inc/args.hpp"
#include "../inc/cvol.hpp"
#include "../inc/log.hpp"
#include "../inc/slider.hpp"

#include <string>

namespace raylib {
#include <raylib.h>
}

void initProgram(int width, int height, bool log_raylib) {

  if (!log_raylib) {
    raylib::SetTraceLogLevel(raylib::LOG_NONE);
  }

  raylib::SetConfigFlags(raylib::FLAG_WINDOW_TRANSPARENT);
  raylib::SetConfigFlags(raylib::FLAG_WINDOW_RESIZABLE);
  raylib::SetWindowState(raylib::FLAG_WINDOW_UNDECORATED);
  raylib::SetTargetFPS(60);

  raylib::InitWindow(width, height, "Hello World!");
}

args parseArgs(int argc, char *argv[]) {
  args val;
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-d" or arg == "--debug") {
      val.debug = true;
    } else if (arg == "-r" or arg == "--raylib_logs") {
      val.raylib_logs = true;
    } else if (arg == "-h" or arg == "--help") {
      val.help = true;
    } else {
      throw std::invalid_argument("Invalid arg: " + arg);
    }
  }

  logln("Parsed arguments.");
  return val;
}

int main(int argc, char *argv[]) {

  args arg;
  try {
    arg = parseArgs(argc, argv);
  } catch (const std::exception &e) {
    logln(e.what());
  }

  if (arg.help) {
    std::cout << "cvol: a simple GUI audio controller\n";
    std::cout << "Argument: \n";
    std::cout << "\t-d, --debug: Enable debug logs\n";
    std::cout << "\t-r, --raylig_logs: Enable raylib logs\n";
    std::cout << "\t-h, --help: Display this help page\n";
    return 0;
  }

  DEBUG_MODE = arg.debug;

  constexpr int SCREEN_WIDTH = 700, SCREEN_HEIGHT = 400;

  volumeController vc;
  slider s(vc.getVolume(), [&vc](int val) {
    vc.setVolume(val);
    logln("Volume set to: " + std::to_string(val));
  });
  initProgram(SCREEN_WIDTH, SCREEN_HEIGHT, arg.raylib_logs);
  logln("Window created.");

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
  logln("Exitting program...");

  raylib::UnloadFont(font);
  raylib::CloseWindow();
  logln("Window closed.");

  return 0;
}
