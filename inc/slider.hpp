#pragma once

#include <functional>

// For DIRECTION
#include "../inc/config.hpp"

namespace raylib {
#include <raylib.h>
}

class slider {
public:
  slider();
  slider(int val);
  slider(int val, const std::function<void(int)> &update_fn);
  slider(int val, const std::function<void(int)> &update_fn,
         const raylib::Rectangle &bar, float radius, const raylib::Color &color,
         const raylib::Color &button_color,
         const raylib::Color &button_line_color,
         const raylib::Color &unused_color,
         const raylib::Color &clicked_button_color,
         const raylib::Color &hovered_button_color, float anim_speed,
         float anim_scale, float seperator_width, DIRECTION slider_direction);

  void render(int val, const raylib::Rectangle &bar, float radius,
              const raylib::Color &color, const raylib::Color &button_color,
              const raylib::Color &button_line_color,
              const raylib::Color &unused_color,
              const raylib::Color &clicked_button_color,
              const raylib::Color &hovered_button_color, float anim_speed,
              float anim_scale, float seperator_width,
              DIRECTION slider_direction);

  void render(int val);

  int getValue() const;

private:
  std::function<void(int)> update_func;
  raylib::Rectangle slider_bar;
  raylib::Rectangle cursor;
  raylib::Color bg;
  raylib::Color bg_enabled;
  raylib::Color btn_bg;
  raylib::Color btn_bg_hovered;
  raylib::Color btn_bg_clicked;
  raylib::Color btn_seperator_bg;
  DIRECTION slider_direction;
  float anim_speed;
  float anim_scale;
  float seperator_width;
  float slider_radius;

  void updateValue(const raylib::Rectangle &bar, DIRECTION slider_direction);
  void draw(const raylib::Rectangle &bar, float radius,
            const raylib::Color &color, const raylib::Color &button_color,
            const raylib::Color &button_line_color,
            const raylib::Color &unused_color,
            const raylib::Color &clicked_button_color,
            const raylib::Color &hovered_button_color, float anim_speed,
            float anim_scale, float seperator_width,
            DIRECTION slider_direction) const;

  void playCursorAnimation(raylib::Rectangle &cursor, float val) const;

  static bool isHovered(const raylib::Rectangle &cursor);
  static bool isClicked(const raylib::Rectangle &cursor);

  int var;
};
