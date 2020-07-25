#include "code/arch/GLFWHelper.hpp"

#include <GLFW/glfw3.h>

#include "code/arch/VKDebugManager.hpp"

cGLFWHelper::cGLFWHelper() {
   this->m_FlagInitDeinit = false;
}

cGLFWHelper::~cGLFWHelper() {
   this->m_WMList.clear(); // Would call all WindowManager's destructor.
   if(this->m_FlagInitDeinit) {
      glfwTerminate();
      this->m_FlagInitDeinit = false;

      DBG_LOG("Terminated GLFW.");
      return;
   }
   DBG_LOG("GLFW already terminated.");
}

void cGLFWHelper::init() {
   this->m_FlagInitDeinit = true;
   glfwInit();
   this->initWH();

   DBG_LOG("Initialized GLFW.");
   
   return;
}

void cGLFWHelper::initWH() {
   glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
   glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
   
#ifdef __APPLE__
   glfwWindowHint(GLFW_COCOA_MENUBAR, GL_TRUE);
   // glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_TRUE);
#endif

   // glfwWindowHint(GLFW_CURSOR)

   return;
}

int cGLFWHelper::registerWindow(int p_WWidth, int p_WHeight, const char * p_WTitle) noexcept {
   if(!p_WTitle || (p_WWidth < 0 || p_WHeight < 0)) {
      std::cerr << "Canceled task to create " << p_WWidth << "x" << p_WHeight << " size of untitled window." << std::endl;
      std::cerr << "Returning window id " << -1 << std::endl;
      return -1;
   }
   size_t res = this->m_WMList.size();
   this->m_WMList.emplace_back(p_WWidth, p_WHeight, p_WTitle);
   return res;
}

cGLFWWindowManager & cGLFWHelper::getWindowManager(int p_WMID) {
   if(p_WMID < 0 || this->m_WMList.size() <= p_WMID) {
      std::cerr << "Failed to get window(" << p_WMID << ")" << std::endl;
      for(cGLFWWindowManager & currentWM : this->m_WMList)
         glfwSetWindowShouldClose(const_cast<GLFWwindow *>(currentWM.getWindow()), GL_TRUE);

      // abort();
   }
   return this->m_WMList.operator[](p_WMID);
}