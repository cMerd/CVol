#define CVOL_VERSION "v0.2.1"

#include "../inc/app.hpp"
#include "../inc/args.hpp"
#include "../inc/config.hpp"
#include "../inc/cvol.hpp"
#include "../inc/errors.hpp"
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

  raylib::SetConfigFlags(
      raylib::FLAG_WINDOW_TRANSPARENT | raylib::FLAG_WINDOW_RESIZABLE |
      raylib::FLAG_WINDOW_UNDECORATED | raylib::FLAG_VSYNC_HINT);

  raylib::InitWindow(width, height, "CVol");
}

int main(int argc, char *argv[]) {

  args arg;
  try {
    arg.parseArgs(argc, argv);
  } catch (const std::exception &e) {
    errorForce(e.what());
    return ERRORS::ARG_ERROR;
  }

  if (arg.version) {
    std::cout << "cvol: a simple GUI audio controller\n";
    std::cout << "version: " << CVOL_VERSION << '\n';
    std::cout << "\'cvol --help\' for more.\n";
    return 0;
  }

  if (arg.help) {
    std::cout << "cvol: a simple GUI audio controller\n";
    std::cout << "version: " << CVOL_VERSION << '\n';
    std::cout << "Argument: \n";
    std::cout << "\t-d, --debug: Enable debug logs\n";
    std::cout << "\t-r, --raylig_logs: Enable raylib logs\n";
    std::cout << "\t-h, --help: Display this help page\n";
    std::cout << "\t-v, --version: Display the version\n";
    std::cout << "\t-c, --config: Load config from custom path\n";
    return 0;
  }

  config_cvol config;
  try {
    config.parse(arg.config);
    logln("Parsed config file");
  } catch (const std::exception &e) {
    errorForce(e.what());
    return ERRORS::CONFIG_ERROR;
  }

  app window(config.width, config.height, "CVol", config.bg, arg.raylib_logs);

  window.loadFont((config.volume_text.font_path).c_str(),
                  config.volume_text.font_size, config.fg);

  volumeController vc;
  slider slider_widget(
      vc.getVolume(), [&vc](int val) { vc.setVolume(val); },
      {config.slider.x, config.slider.y, config.slider.width,
       config.slider.height},
      config.slider.radius, config.slider.enabled_bg, config.slider.button.bg,
      config.slider.button.seperator_color, config.slider.disabled_bg,
      config.slider.button.click_bg, config.slider.button.hover_bg,
      config.slider.button.anim.speed, config.slider.button.anim.scale,
      config.slider.button.seperator_width, config.slider.direction);

  while (!window.shouldClose()) {
    window.clear();

    // slider
    slider_widget.render(vc.getVolume());

    // volume text
    DrawTextEx(
        window.getFont(),
        (config.volume_text.volume_label +
         std::to_string(slider_widget.getValue()) + "%")
            .c_str(),
        (raylib::Vector2){config.volume_text.x_pos, config.volume_text.y_pos},
        config.volume_text.font_size, 2, config.fg);

    window.process();
  }

  return 0;
}
