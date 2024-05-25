#pragma once

#include <functional>

namespace raylib {
#include <raylib.h>
}

class slider {
public:
  std::function<void(int)> update_func;
  slider();
  slider(int val);
  slider(int val, const std::function<void(int)> &update_fn);

  void render(int val, const raylib::Rectangle &bar, float radius,
              const raylib::Color &color, const raylib::Color &button_color,
              const raylib::Color &button_line_color,
              const raylib::Color &unused_color,
              const raylib::Color &clicked_button_color,
              const raylib::Color &hovered_button_color, float anim_speed,
              float anim_scale, float seperator_width);

  int getValue() const;

private:
  void updateValue(const raylib::Rectangle &bar);
  void draw(const raylib::Rectangle &bar, float radius,
            const raylib::Color &color, const raylib::Color &button_color,
            const raylib::Color &button_line_color,
            const raylib::Color &unused_color,
            const raylib::Color &clicked_button_color,
            const raylib::Color &hovered_button_color, float anim_speed,
            float anim_scale, float seperator_width) const;

  void playCursorAnimation(raylib::Rectangle &cursor, float val) const;

  static bool isHovered(const raylib::Rectangle &cursor);
  static bool isClicked(const raylib::Rectangle &cursor);

  int var;
};
