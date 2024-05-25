#include "../inc/args.hpp"
#include "../inc/log.hpp"
#include <stdexcept>

void args::parseArgs(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-d" or arg == "--debug") {
      this->debug = true;
    } else if (arg == "-r" or arg == "--raylib_logs") {
      this->raylib_logs = true;
    } else if (arg == "-h" or arg == "--help") {
      this->help = true;
    } else if (arg == "-v" or arg == "--version") {
      this->version = true;
    } else if (arg == "-c" or arg == "--config") {
      if (i == argc - 1) {
        throw std::logic_error("-c/--config requires config file path.");
      }
      this->config = argv[++i];
    } else {
      throw std::invalid_argument("Invalid arg: " + arg);
    }
  }
  DEBUG_MODE = this->debug;
  logln("Parsed arguments.");
}
