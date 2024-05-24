#pragma once

#include <cstdint>
#include <string>

namespace raylib {
#include <raylib.h>
}

struct anim_config {
  float scale;
  float speed;
  bool enabled;
};

struct button_config {
  raylib::Color bg;
  raylib::Color hover_bg;
  raylib::Color click_bg;
  raylib::Color seperator_color;
  anim_config anim;
  float seperator_width;
};

struct slider_config {
  raylib::Color disabled_bg;
  raylib::Color enabled_bg;
  button_config button;
  float x;
  float y;
  float width;
  float height;
  float radius;
};

struct vol_config {
  std::string volume_label;
  float xPos;
  float yPos;
  int fontSize;
};

class config_cvol {
public:
  raylib::Color bg;
  raylib::Color fg;
  slider_config slider;
  vol_config volume_text;
  uint32_t width;
  uint32_t height;

  void parse(const std::string &config_path);
  static std::string getConfigPath();

private:
  static raylib::Color hexToColor(const std::string &hex);
  static bool isValidHexColor(const std::string &hex);
  static uint16_t hexToUint16(const std::string &hex);
};
