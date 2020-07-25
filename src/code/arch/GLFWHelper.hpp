#ifndef CODE_ARCH_GLFWHELPER_HPP
#define CODE_ARCH_GLFWHELPER_HPP

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

	/**
	 * @return The index number of current wm.
	 */
	int registerWindow(int, int, const char *) noexcept;

	cGLFWWindowManager & getWindowManager(int);
};

#endif // CODE_ARCH_GLFWHELPER_HPP