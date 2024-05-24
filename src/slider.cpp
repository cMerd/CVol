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
                    const raylib::Color &hovered_button_color, float anim_speed,
                    float anim_scale, float seperator_width) {
  this->draw(bar, radius, color, button_color, button_line_color, unused_color,
             clicked_button_color, hovered_button_color, anim_speed, anim_scale,
             seperator_width);
  this->updateValue(bar);
}

void slider::cursor_anim(raylib::Rectangle &cursor, float val) const {
  float deltaWidth = cursor.width * val;
  float deltaHeight = cursor.height * val;
  cursor.width *= 1.0f + val;
  cursor.height *= 1.0f + val;
  cursor.x -= deltaWidth / 2.0f;
  cursor.y -= deltaHeight / 2.0f;
}

void slider::draw(const raylib::Rectangle &bar, float radius,
                  const raylib::Color &color, const raylib::Color &button_color,
                  const raylib::Color &button_line_color,
                  const raylib::Color &unused_color,
                  const raylib::Color &clicked_button_color,
                  const raylib::Color &hovered_button_color,
                  float animation_speed, float anim_scale,
                  float seperator_width) const {
  raylib::Rectangle cursor;
  cursor.width = bar.width / 10.0f;
  cursor.height = bar.height + 5.0f;
  cursor.x = (bar.x + (bar.width * var / 100.0f)) - cursor.width / 2.0f;
  cursor.y = bar.y - 2.0f;

  float original_height = cursor.height;
  float animation_target = 0.0f;

  // unused (background) bar
  raylib::DrawRectangleRounded(bar, radius, 1, unused_color);

  // used area
  raylib::DrawRectangleRounded(
      {bar.x, bar.y, cursor.x - bar.x + cursor.width, bar.height}, radius, 1,
      color);

  raylib::Color cursor_color;
  if (this->isClicked(cursor)) {
    cursor_color = clicked_button_color;
    animation_target = anim_scale;
  } else if (this->isHovered(cursor)) {
    cursor_color = hovered_button_color;
    animation_target = anim_scale;
  } else {
    cursor_color = button_color;
    animation_target = 0.0f;
  }

  // Smooth the animation by interpolating the animation_value
  // Smoothing hover animation
  static float animation_value = 0.0f; // this doesn't get out of scope, so it
                                       // gets larger every animation frame
  animation_value += (animation_target - animation_value) * animation_speed;
  this->cursor_anim(cursor, animation_value);

  raylib::DrawRectangleRounded(cursor, radius, 1, cursor_color);

  // Calculate the number of separators based on the original cursor height
  float separator_start = cursor.y + (20.0f);
  float separator_end = cursor.y + original_height - 10.0f;

  for (float i = separator_start; i <= separator_end; i += 10.0f) {
    raylib::DrawLine(cursor.x + ((cursor.width - seperator_width) / 2), i,
                     cursor.x + cursor.width -
                         ((cursor.width - seperator_width) / 2),
                     i, button_line_color);
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
