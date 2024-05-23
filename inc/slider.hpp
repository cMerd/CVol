
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

  void render(const raylib::Rectangle &bar, float radius,
              const raylib::Color &color, const raylib::Color &button_color,
              const raylib::Color &button_line_color,
              const raylib::Color &unused_color,
              const raylib::Color &clicked_button_color,
              const raylib::Color &hovered_button_color);

  int getValue() const;

private:
  void updateValue(const raylib::Rectangle &bar);
  void draw(const raylib::Rectangle &bar, float radius,
            const raylib::Color &color, const raylib::Color &button_color,
            const raylib::Color &button_line_color,
            const raylib::Color &unused_color,
            const raylib::Color &clicked_button_color,
            const raylib::Color &hovered_button_color) const;

  static bool isHovered(const raylib::Rectangle &cursor);
  static bool isClicked(const raylib::Rectangle &cursor);

  int var;
};
