#ifndef WIN_HPP
#define WIN_HPP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>

namespace gl {
   struct _WindowConfigs {
   private:
      struct Window& w;
   public:
      _WindowConfigs(struct Window& _w)         : w(_w) { glfwWindowHint(GLFW_DOUBLEBUFFER, 1); glfwWindowHint(GLFW_RESIZABLE, 1); glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API); glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); }
      _WindowConfigs& depth_bits(int bits)      { glfwWindowHint(GLFW_DEPTH_BITS, bits);   return *this; }
      _WindowConfigs& without_double_buffer()   { glfwWindowHint(GLFW_DOUBLEBUFFER, 0); return *this; }
      _WindowConfigs& without_resizing()        { glfwWindowHint(GLFW_DOUBLEBUFFER, 0); return *this; }
      struct Window& bk()                       { return w; }
   };

   static void _error(int error, const char* description) { fputs(description, stderr); }
   void _resize_cb(GLFWwindow* window, int w, int h);

   struct Window {
      GLFWwindow* w{ nullptr };

      _WindowConfigs config(int maj_ver, int min_ver) { glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj_ver); glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min_ver); glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); return { *this }; }
      Window& mk(int _w, int _h, char const* name = "oh, hi!") { w = glfwCreateWindow(_w, _h, name, NULL, NULL); if (!w) { glfwTerminate(); abort(); } glfwMakeContextCurrent(w); glewExperimental = GL_TRUE; glewInit(); glGetError(); glfwMakeContextCurrent(w); glfwSwapInterval(1); glClearColor(0,0,0,1); /*resize_cb(gl::_resize_cb);*/ return *this; }
      Window& mk(char const* name = "oh, hi!") { return mk(640, 480, name); }
      Window& key_cb(void(*key)(GLFWwindow* w, int key, int scancode, int action, int mode)) { glfwSetKeyCallback(w, key); return *this; }
      Window& resize_cb(void(*resize)(GLFWwindow* w, int width, int height)) { glfwSetWindowSizeCallback(w, resize); return *this; }
      bool is_active() { return !glfwWindowShouldClose(w); }
      void clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
      void show() { glfwSwapBuffers(w); glfwPollEvents(); }
      void draw(GLenum type, GLsizei vert_num, GLint offset = 0) { glDrawArrays(GL_TRIANGLES, offset, vert_num); }
      void draw_by_order(GLenum type, GLuint element_num) { glDrawElements(GL_TRIANGLES, element_num, GL_UNSIGNED_INT, 0); }
      Window& as(GLFWwindow*& _w) { _w = w; return *this; }
      Window(GLFWwindow* _w) : w(_w) {}
      Window() {}
      void close() { glfwDestroyWindow(w); glfwTerminate(); }
      static GLint __width, __height;
   };

   static void _resize_cb(GLFWwindow* window, int w, int h)
   {
      gl::Window::__width = w;
      gl::Window::__height = h;
      glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   }

   namespace For {
      static gl::Window window(GLFWwindow* w) { return gl::Window(w); }
      static gl::Window window() { glfwSetErrorCallback(_error); if (!glfwInit()) abort(); return gl::Window(); }
   }
}


#endif WIN_HPP
