#ifndef SRC_CODE_ARCH_GLFWHELPER_HPP
#define SRC_CODE_ARCH_GLFWHELPER_HPP

#include "GLFWWindowManager.hpp"

#include <vector>

class cGLFWHelper {
   bool m_FlagInitDeinit;

   std::vector<cGLFWWindowManager> m_WMList;

   // init window hints
   void initWH();
public:
   explicit cGLFWHelper();
   ~cGLFWHelper();

   void init();

   int registerWindow(int, int, const char *) noexcept;

   cGLFWWindowManager & getWindowManager(int);
};

#endif // SRC_CODE_ARCH_GLFWHELPER_HPP