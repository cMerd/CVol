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

/*
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

  // animation to play on hover
  // TODO: Make it smoother
  auto animation_scale = [](float val, raylib::Rectangle &cursor) {
    float deltaWidth = cursor.width * val;
    float deltaHeight = cursor.height * val;
    cursor.width *= 1.0 + val;
    cursor.height *= 1.0 + val;
    cursor.x -= deltaWidth / 2;
    cursor.y -= deltaHeight / 2;
  };

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
    animation_scale(0.1, cursor);
  } else if (this->isHovered(cursor)) {
    cursor_color = hovered_button_color;
    animation_scale(0.1, cursor);
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
*/

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
  float original_height = cursor.height; // for seperators to find the correct
                                         // height even if animation plays

  float animation_target = 0.0f;

  auto animation_scale = [](float val, raylib::Rectangle &cursor) {
    float deltaWidth = cursor.width * val;
    float deltaHeight = cursor.height * val;
    cursor.width *= 1.0f + val;
    cursor.height *= 1.0f + val;
    cursor.x -= deltaWidth / 2.0f;
    cursor.y -= deltaHeight / 2.0f;
  };

  // unused (background) bar
  raylib::DrawRectangleRounded(bar, radius, 1, unused_color);

  // used area
  raylib::DrawRectangleRounded(
      {bar.x, bar.y, cursor.x - bar.x + cursor.width, bar.height}, radius, 1,
      color);

  raylib::Color cursor_color;
  if (this->isClicked(cursor)) {
    cursor_color = clicked_button_color;
    animation_target = 0.1f;
  } else if (this->isHovered(cursor)) {
    cursor_color = hovered_button_color;
    animation_target = 0.1f;
  } else {
    cursor_color = button_color;
    animation_target = 0.0f;
  }

  // Smooth the animation by interpolating the animation_value
  // Smoothing hover animation
  static float animation_value = 0.0f; // this doesn't get out of scope, so it
                                       // gets larger every animation frame
  float animation_speed = 0.1f;
  animation_value += (animation_target - animation_value) * animation_speed;
  float anim_val = animation_value;
  animation_scale(animation_value, cursor);

  raylib::DrawRectangleRounded(cursor, radius, 1, cursor_color);

  // Calculate the number of separators based on the original cursor height
  float separator_start =
      cursor.y + (20.0f) * (anim_val != 0.0f ? 1.0f + anim_val : 1);
  float separator_end = cursor.y + original_height - 10.0f;

  for (float i = separator_start; i <= separator_end; i += 10.0f) {
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
