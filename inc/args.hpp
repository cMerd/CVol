#pragma once

#include "../inc/config.hpp"
#include <string>

class args {
public:
  bool debug = false;
  bool raylib_logs = false;
  bool help = false;
  bool version = false;
  std::string config = config_cvol::getConfigPath();

  void parseArgs(int argc, char *argv[]);
};
