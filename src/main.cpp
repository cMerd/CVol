#define CVOL_VERSION "v0.1.0"

#include "../inc/args.hpp"
#include "../inc/config.hpp"
#include "../inc/cvol.hpp"
#include "../inc/log.hpp"
#include "../inc/slider.hpp"

#include <iostream>
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

  raylib::InitWindow(width, height, "CVol");
}

int main(int argc, char *argv[]) {

  args arg;
  config_cvol config;
  volumeController vc;
  slider slider_widget(vc.getVolume(), [&vc](int val) {
    vc.setVolume(val);
    logln("Volume set to: " + std::to_string(val));
  });

  try {
    arg.parseArgs(argc, argv);
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

  try {
    config.parse(arg.config);
    logln("Parsed config file");
  } catch (const std::exception &e) {
    errorForce(e.what());
    return 2;
  }

  initProgram(config.width, config.height, arg.raylib_logs);
  logln("Window created.");

  raylib::Font font = raylib::LoadFontEx((config.volume_text.font_path).c_str(),
                                         config.volume_text.font_size, NULL, 0);

  while (!raylib::WindowShouldClose()) {
    raylib::BeginDrawing();
    raylib::ClearBackground(config.bg);

    // volume text
    DrawTextEx(
        font,
        (config.volume_text.volume_label + std::to_string(vc.getVolume()) + "%")
            .c_str(),
        (raylib::Vector2){config.volume_text.x_pos, config.volume_text.y_pos},
        config.volume_text.font_size, 2, config.fg);

    // slider
    slider_widget.render(
        {config.slider.x, config.slider.y, config.slider.width,
         config.slider.height},
        config.slider.radius, config.slider.enabled_bg, config.slider.button.bg,
        config.slider.button.seperator_color, config.slider.disabled_bg,
        config.slider.button.click_bg, config.slider.button.hover_bg,
        config.slider.button.anim.speed, config.slider.button.anim.scale,
        config.slider.button.seperator_width);

    raylib::EndDrawing();
  }
  logln("Exitting program...");

  raylib::UnloadFont(font);
  logln("Unloaded font.");

  raylib::CloseWindow();
  logln("Window closed.");

  return 0;
}
