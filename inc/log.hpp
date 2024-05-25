#pragma once

#include <iostream>

// forced functions won't check if debug mode is on
extern bool DEBUG_MODE;

template <typename T> void logln(const T &el) {
  if (DEBUG_MODE) {
    std::cout << "[INFO]: " << el << '\n';
  }
}

template <typename T> void warnln(const T &el) {
  if (DEBUG_MODE) {
    std::cout << "[WARNING]: " << el << '\n';
  }
}

template <typename T> void errorln(const T &el) {
  if (DEBUG_MODE) {
    std::cout << "[ERROR]: " << el << '\n';
  }
}

template <typename T> void log(const T &el) {
  if (DEBUG_MODE) {
    std::cout << "[INFO]: " << el << ' ';
  }
}

template <typename T> void warn(const T &el) {
  if (DEBUG_MODE) {
    std::cout << "[WARNING]: " << el << ' ';
  }
}

template <typename T> void error(const T &el) {
  if (DEBUG_MODE) {
    std::cout << "[ERROR]: " << el << ' ';
  }
}

template <typename T> void logForce(const T &el) {
  std::cout << "[INFO]: " << el << '\n';
}

template <typename T> void warnForce(const T &el) {
  std::cout << "[WARNING]: " << el << '\n';
}

template <typename T> void errorForce(const T &el) {
  std::cout << "[ERROR]: " << el << '\n';
}
