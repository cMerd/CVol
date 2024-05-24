#include "../inc/config.hpp"
#include "../inc/log.hpp"
#include <fstream>

#include <json/json.h>

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

void config_cvol::parse(const std::string &config_path) {
  std::ifstream file_input(config_path);

  if (!file_input.is_open()) {
    throw std::invalid_argument("Couldn't open file: " + config_path);
  }

  Json::Value config;
  Json::CharReaderBuilder builder;
  JSONCPP_STRING errs;

  builder["collectComments"] = true;
  if (!parseFromStream(builder, file_input, &config, &errs)) {
    throw std::runtime_error(errs);
  }

  logln("Loaded config file: " + config_path);

  this->width = config["window"]["width"].asUInt();
  this->height = config["window"]["height"].asUInt();
  this->bg = hexToColor(config["window"]["bg"].asString());
  this->fg = hexToColor(config["window"]["fg"].asString());
  logln("Loaded window config.");

  this->slider.x = config["slider"]["xPos"].asFloat();
  this->slider.y = config["slider"]["yPos"].asFloat();
  this->slider.width = config["slider"]["width"].asFloat();
  this->slider.height = config["slider"]["height"].asFloat();
  this->slider.radius = config["slider"]["radius"].asFloat();
  this->slider.disabled_bg =
      hexToColor(config["slider"]["disabled_bg"].asString());
  this->slider.enabled_bg =
      hexToColor(config["slider"]["enabled_bg"].asString());
  logln("Loaded slider config");

  this->slider.button.seperator_width =
      config["slider"]["button"]["seperator_width"].asFloat();
  this->slider.button.bg =
      hexToColor(config["slider"]["button"]["bg"].asString());
  this->slider.button.hover_bg =
      hexToColor(config["slider"]["button"]["hover_bg"].asString());
  this->slider.button.click_bg =
      hexToColor(config["slider"]["button"]["click_bg"].asString());
  this->slider.button.seperator_color =
      hexToColor(config["slider"]["button"]["seperator_color"].asString());
  logln("Loaded button config");

  this->slider.button.anim.enabled =
      config["slider"]["button"]["animation"]["enabled"].asBool();
  this->slider.button.anim.scale =
      config["slider"]["button"]["animation"]["scale"].asFloat();
  this->slider.button.anim.speed =
      config["slider"]["button"]["animation"]["speed"].asFloat();
  logln("Loaded animation config");

  this->volume_text.volume_label =
      config["volume_text"]["volume_label"].asString();
  this->volume_text.xPos = config["volume_text"]["xPos"].asFloat();
  this->volume_text.yPos = config["volume_text"]["yPos"].asFloat();
  this->volume_text.fontSize = config["volume_text"]["font_size"].asUInt();
  logln("Loaded volume text config.");
}

raylib::Color config_cvol::hexToColor(const std::string &hex) {
  if (!config_cvol::isValidHexColor(hex)) {
    throw std::logic_error(std::string("Invalid hex data: " + hex));
  }

  std::array<uint16_t, 4> color_values = {0, 0, 0, 255};

  for (size_t i = 1; i < hex.size(); i += 2) {
    std::string var = hex.substr(i, 2);
    color_values[(i - 1) / 2] = hexToUint16(var);
  }

  raylib::Color col;
  col.r = color_values[0];
  col.g = color_values[1];
  col.b = color_values[2];
  col.a = color_values[3];
  return col;
}

uint16_t config_cvol::hexToUint16(const std::string &hex) {
  uint16_t x;
  std::stringstream ss;
  ss << std::hex << hex;
  ss >> x;
  return x;
}

bool config_cvol::isValidHexColor(const std::string &hex) {
  // Hex colors look like this: #RRGGBBAA
  // Where R is for red, G - green, B - blue values, A - alpha
  // And they're written in hex, which is base 16:
  // 0 1 2 3 4 5 6 7 8 9 A B C D E F are allowed digits

  if ((hex.size() != 7 and hex.size() != 9) or hex.front() != '#') {
    return false;
  }

  const std::string valid_chars = "#0123456789ABCDEFabcdef";

  for (const char &c : hex) {
    if (valid_chars.find(c) == std::string::npos) {
      return false;
    }
  }

  return true;
}

std::string config_cvol::getConfigPath() {
  passwd *pw = getpwuid(getuid());
  std::string home_dir = pw->pw_dir;
  std::string config_path = home_dir + "/.config/cvol/config.json";
  logln("Home directory: " + home_dir);
  logln("Config path: " + config_path);
  return config_path;
}
