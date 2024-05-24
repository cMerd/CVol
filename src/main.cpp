#define CVOL_VERSION "v0.1.0"

#include "../inc/args.hpp"
#include "../inc/config.hpp"
#include "../inc/cvol.hpp"
#include "../inc/log.hpp"
#include "../inc/slider.hpp"

#include <string>
#include <iostream>

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

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

std::string getConfigPath() {
  passwd *pw = getpwuid(getuid());
  std::string home_dir = pw->pw_dir;
  std::string config_path = home_dir + "/.config/cvol/config.json";
  logln("Home directory: " + home_dir);
  logln("Config path: " + config_path);
  return config_path;
}

args parseArgs(int argc, char *argv[]) {

  args val = {.debug = false,
              .raylib_logs = false,
              .help = false,
              .version = false,
              .config = getConfigPath()};

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-d" or arg == "--debug") {
      val.debug = true;
    } else if (arg == "-r" or arg == "--raylib_logs") {
      val.raylib_logs = true;
    } else if (arg == "-h" or arg == "--help") {
      val.help = true;
    } else if (arg == "-v" or arg == "--version") {
      val.version = true;
    } else if (arg == "-c" or arg == "--config") {
      if (i == argc - 1) {
        throw std::logic_error("-c/--config requires config file path.");
      }
      val.config = argv[++i];
    } else {
      throw std::invalid_argument("Invalid arg: " + arg);
    }
  }

  return val;
}

int main(int argc, char *argv[]) {

  args arg;

  try {
    arg = parseArgs(argc, argv);
    logln("Parsed arguments.");
  } catch (const std::exception &e) {
    errorForce(e.what());
    return 1;
  }

  if (arg.version) {
    std::cout << "cvol: a simple GUI audio controller\n";
    std::cout << "version: " << CVOL_VERSION << '\n';
    std::cout << "\'cvol --help\' for more.\n";
  }

  if (arg.help) {
    std::cout << "cvol: a simple GUI audio controller\n";
    std::cout << "version: " << CVOL_VERSION << '\n';
    std::cout << "Argument: \n";
    std::cout << "\t-d, --debug: Enable debug logs\n";
    std::cout << "\t-r, --raylig_logs: Enable raylib logs\n";
    std::cout << "\t-h, --help: Display this help page\n";
    return 0;
  }

  config_cvol config;
  try {
    config.parse(arg.config);
    logln("Parsed config file");
  } catch (const std::exception &e) {
    errorForce(e.what());
    return 2;
  }

  DEBUG_MODE = arg.debug;

  volumeController vc;
  slider s(vc.getVolume(), [&vc](int val) {
    vc.setVolume(val);
    logln("Volume set to: " + std::to_string(val));
  });
  initProgram(config.width, config.height, arg.raylib_logs);
  logln("Window created.");

  const raylib::Font font =
      raylib::LoadFontEx((std::string(raylib::GetApplicationDirectory()) +
                          std::string("../assets/font.ttf"))
                             .c_str(),
                         config.volume_text.fontSize, NULL, 0);

  while (!raylib::WindowShouldClose()) {
    raylib::BeginDrawing();
    raylib::ClearBackground(config.bg);

    DrawTextEx(
        font,
        (config.volume_text.volume_label + std::to_string(vc.getVolume()) + "%")
            .c_str(),
        (raylib::Vector2){config.volume_text.xPos, config.volume_text.yPos},
        config.volume_text.fontSize, 2, config.fg);

    s.render({config.slider.x, config.slider.y, config.slider.width,
              config.slider.height},
             config.slider.radius, config.slider.enabled_bg,
             config.slider.button.bg, config.slider.button.seperator_color,
             config.slider.disabled_bg, config.slider.button.click_bg,
             config.slider.button.hover_bg, config.slider.button.anim.speed,
             config.slider.button.anim.scale,
             config.slider.button.seperator_width);

    logln(config.slider.button.seperator_width);

    raylib::EndDrawing();
  }
  logln("Exitting program...");

  raylib::UnloadFont(font);
  raylib::CloseWindow();
  logln("Window closed.");

  return 0;
}
