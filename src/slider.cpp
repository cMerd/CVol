#include "./../inc/slider.hpp"

namespace raylib {
#include <raylib.h>
}

slider::slider() {}

slider::slider(int val) { this->var = val; }

slider::slider(int val, const std::function<void(int)> &update_fn) {
  this->var = val;
  this->update_func = update_fn;
}

void slider::render(const raylib::Rectangle &bar, float radius,
                    const raylib::Color &color,
                    const raylib::Color &button_color,
                    const raylib::Color &button_line_color,
                    const raylib::Color &unused_color,
                    const raylib::Color &clicked_button_color,
                    const raylib::Color &hovered_button_color) {
  this->draw(bar, radius, color, button_color, button_line_color, unused_color,
             clicked_button_color, hovered_button_color);
  this->updateValue(bar);
}

void slider::draw(const raylib::Rectangle &bar, float radius,
                  const raylib::Color &color, const raylib::Color &button_color,
                  const raylib::Color &button_line_color,
                  const raylib::Color &unused_color,
                  const raylib::Color &clicked_button_color,
                  const raylib::Color &hovered_button_color) const {
  raylib::Rectangle cursor;
  cursor.width = bar.width / 10.0f;
  cursor.height = bar.height + 5.0f;
  cursor.x = (bar.x + (bar.width * var / 100.0f)) - cursor.width / 2.0f;
  cursor.y = bar.y - 2.0f;

  // unused (background) bar
  raylib::DrawRectangleRounded(bar, radius, 1, unused_color);

  // used area
  raylib::DrawRectangleRounded(
      {bar.x, bar.y, cursor.x - bar.x + cursor.width, bar.height}, radius, 1,
      color);

  // cursor
  raylib::Color cursor_color;
  if (this->isClicked(cursor)) {
    cursor_color = clicked_button_color;
  } else if (this->isHovered(cursor)) {
    cursor_color = hovered_button_color;
  } else {
    cursor_color = button_color;
  }

  raylib::DrawRectangleRounded(cursor, radius, 1, cursor_color);

  for (float i = cursor.y + 20.0f; i <= cursor.y + cursor.height - 10.0f;
       i += 10.0f) {
    raylib::DrawLine(cursor.x + 5.0f, i, cursor.x + cursor.width - 5.0f, i,
                     button_line_color);
  }
}

void slider::updateValue(const raylib::Rectangle &bar) {

  if (!this->isClicked(bar)) {
    return;
  }

  // bar.x + (bar.width * var / 100) = raylib::GetMouseX();
  // bar.width * var / 100 = raylib::GetMouseX() - bar.x;
  // bar.width * var = (raylib::GetMouseX() - bar.x) * 100;
  // var = (raylib::GetMouseX() - bar.x) * 100 / bar.width;

  int mouseX = raylib::GetMouseX();
  var = (mouseX - bar.x) * 100 / bar.width;

  if (var < 0) {
    var = 0;
  }
  if (var > 100) {
    var = 100;
  }

  this->update_func(var);
}

int slider::getValue() const { return this->var; }

bool slider::isHovered(const raylib::Rectangle &cursor) {
  return raylib::CheckCollisionPointRec(raylib::GetMousePosition(), cursor);
}

bool slider::isClicked(const raylib::Rectangle &cursor) {
  return (raylib::CheckCollisionPointRec(raylib::GetMousePosition(), cursor) and
          raylib::IsMouseButtonDown(raylib::MOUSE_BUTTON_LEFT));
}
