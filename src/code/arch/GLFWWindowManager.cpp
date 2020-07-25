#include "code/arch/GLFWWindowManager.hpp"

#include <GLFW/glfw3.h>

#include "code/arch/VKDebugManager.hpp"

cGLFWWindowManager::cGLFWWindowManager(int p_WindowWidth, int p_WindowHeight, const char * p_WindowTitle) {
	this->m_Window = glfwCreateWindow(p_WindowWidth, p_WindowHeight, p_WindowTitle, nullptr, nullptr);

	DBG_LOG("Created window object(:" << m_Window << ").");

}

cGLFWWindowManager::~cGLFWWindowManager() {
	glfwDestroyWindow(this->m_Window);

	DBG_LOG("Destroyed window object(:" << m_Window << ").");
}

const GLFWwindow * cGLFWWindowManager::getWindow() noexcept {
	return this->m_Window;
}