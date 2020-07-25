#ifndef CODE_ARCH_GLFWWINDOWMANAGER_HPP
#define CODE_ARCH_GLFWWINDOWMANAGER_HPP

class GLFWwindow;

class cGLFWWindowManager {
	GLFWwindow * m_Window;

public:
	explicit cGLFWWindowManager(int p_WindowWidth, int p_WindowHeight, const char * p_WindowTitle);
	~cGLFWWindowManager();

	const GLFWwindow * getWindow() noexcept;
};

#endif // CODE_ARCH_GLFWWINDOWMANAGER_HPP