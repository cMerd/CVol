
#include <string>

namespace raylib {
#include <raylib.h>
}

class app {
public:
  app(int width, int height, const std::string &title, const raylib::Color &col,
      bool log_raylib);
  ~app();

  void loadFont(const std::string &font_path, int font_size,
                const raylib::Color &fg);

  bool shouldClose() const;
  void clear() const;
  void process() const;
  void drawText(const std::string &text, float xPos, float yPos) const;
  raylib::Font getFont() const;

private:
  bool log;
  raylib::Color bg, fg;
  raylib::Font font;
  int fontSize;
};
