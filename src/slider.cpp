#include "../inc/slider.hpp"

// For DIRECTION
#include "../inc/config.hpp"

namespace raylib {
#include <raylib.h>
}

#include <stdexcept>

slider::slider() {}

slider::slider(int val) { this->var = val; }

slider::slider(int val, const std::function<void(int)> &update_fn) {
  this->var = val;
  this->update_func = update_fn;
}

slider::slider(int val, const std::function<void(int)> &update_fn,
               const raylib::Rectangle &bar, float radius,
               const raylib::Color &color, const raylib::Color &button_color,
               const raylib::Color &button_line_color,
               const raylib::Color &unused_color,
               const raylib::Color &clicked_button_color,
               const raylib::Color &hovered_button_color, float anim_speed,
               float anim_scale, float seperator_width,
               DIRECTION slider_direction) {
  this->var = val;
  this->update_func = update_fn;
  this->slider_bar = bar;
  this->bg = unused_color;
  this->bg_enabled = color;
  this->slider_radius = radius;
  this->btn_bg = button_color;
  this->btn_bg_hovered = hovered_button_color;
  this->btn_bg_clicked = clicked_button_color;
  this->anim_speed = anim_speed;
  this->anim_scale = anim_scale;
  this->slider_direction = slider_direction;
  this->seperator_width = seperator_width;
  this->btn_seperator_bg = button_line_color;
}

void slider::render(int val) {

  this->var = val;

  switch (slider_direction) {
  case VERTICAL:
    cursor.width = this->slider_bar.width / 10.0f;
    cursor.height = this->slider_bar.height + 5.0f;
    cursor.x = (this->slider_bar.x + (this->slider_bar.width * var / 100.0f)) -
               cursor.width / 2.0f;
    cursor.y = this->slider_bar.y - 2.0f;
    break;
  case HORIZONTAL:
    cursor.width = this->slider_bar.width + 5.0f;
    cursor.height = this->slider_bar.height / 10.0f;
    cursor.x = this->slider_bar.x - 2.0f;
    cursor.y = (this->slider_bar.y + (this->slider_bar.height * var / 100.0f) -
                cursor.height / 2.0f);
    break;
  default:
    throw std::logic_error("Invalid direction.");
    break;
  }
  float original_height = cursor.height;
  float animation_target = 0.0f;

  // unused (background) bar
  raylib::DrawRectangleRounded(this->slider_bar, this->slider_radius, 1,
                               this->bg);

  // used area
  raylib::DrawRectangleRounded(
      {this->slider_bar.x, this->slider_bar.y,
       this->cursor.x - this->slider_bar.x + cursor.width,
       this->slider_bar.height},
      this->slider_radius, 1, this->bg_enabled);

  raylib::Color cursor_color;
  if (this->isClicked(cursor)) {
    cursor_color = this->btn_bg_clicked;
    animation_target = anim_scale;
  } else if (this->isHovered(cursor)) {
    cursor_color = this->btn_bg_hovered;
    animation_target = anim_scale;
  } else {
    cursor_color = this->btn_bg;
    animation_target = 0.0f;
  }

  // Smooth the animation by interpolating the animation_value
  // Smoothing hover animation
  static float animation_value = 0.0f; // this doesn't get out of scope, so it
                                       // gets larger every animation frame
  animation_value += (animation_target - animation_value) * this->anim_speed;

  this->playCursorAnimation(cursor, animation_value);

  raylib::DrawRectangleRounded(cursor, this->slider_radius, 1, cursor_color);

  // Calculate the number of separators based on the original cursor height
  float separator_start = cursor.y + (20.0f);
  float separator_end = cursor.y + original_height - 10.0f;

  for (float i = separator_start; i <= separator_end; i += 10.0f) {
    raylib::DrawLine(cursor.x + ((cursor.width - seperator_width) / 2), i,
                     cursor.x + cursor.width -
                         ((cursor.width - seperator_width) / 2),
                     i, this->btn_seperator_bg);
  }

  this->updateValue(this->slider_bar, slider_direction);
}

void slider::playCursorAnimation(raylib::Rectangle &cursor, float val) const {
  float deltaWidth = cursor.width * val;
  float deltaHeight = cursor.height * val;
  cursor.width *= 1.0f + val;
  cursor.height *= 1.0f + val;
  cursor.x -= deltaWidth / 2.0f;
  cursor.y -= deltaHeight / 2.0f;
}

void slider::updateValue(const raylib::Rectangle &bar,
                         DIRECTION slider_direction) {

  if (!this->isClicked(bar)) {
    return;
  }

  // bar.x + (bar.width * var / 100) = raylib::GetMouseX();
  // bar.width * var / 100 = raylib::GetMouseX() - bar.x;
  // bar.width * var = (raylib::GetMouseX() - bar.x) * 100;
  // var = (raylib::GetMouseX() - bar.x) * 100 / bar.width;
  switch (slider_direction) {
  case VERTICAL: {
    int mouseX = raylib::GetMouseX();
    var = (mouseX - bar.x) * 100 / bar.width;
    break;
  }
  case HORIZONTAL: {
    int mouseY = raylib::GetMouseY();
    var = (mouseY - bar.y) * 100 / bar.height;
    break;
  }
  default:
    throw std::logic_error("Invalid direction");
    break;
  }

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
