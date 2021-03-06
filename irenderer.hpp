#ifndef IRENDERER_HPP
#define IRENDERER_HPP
#include <gtc/matrix_transform.hpp>

struct IRenderer {
   virtual void setup(glm::uvec2 window_size, int &width, int &height, char const *title, bool fullscreen) = 0;
   virtual void clear(glm::ivec3 color) = 0;
   virtual void draw_line(glm::vec2 from, glm::vec2 to, glm::ivec4 color) = 0;
   virtual void show(void) = 0;
   virtual bool is_closed() = 0;
   virtual void shutdown() = 0;
};

#endif // IRENDERER_HPP
