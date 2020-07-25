#ifndef CODE_ARCH_VKEXCEPTIONHANDLER_HPP
#define CODE_ARCH_VKEXCEPTIONHANDLER_HPP

#include <iostream>
#include <vulkan/vulkan.h>

void handleGLFWResult(bool p_ResultFlag, const char * p_FailedMsg, const char * p_SuccessMsg = nullptr) noexcept {
	if(p_ResultFlag) {
		std::cerr << "[GLFWExceptionHandler]: " << p_FailedMsg << std::endl;
		return;
	}
	if(p_SuccessMsg)
		std::cerr << p_SuccessMsg << std::endl;
}

void handleVKResult(const VkResult & p_Result, const char * p_FailedMsg, const char * p_SuccessMsg = nullptr) noexcept {
	if(p_Result) {
		std::cerr << "[VKExceptionHandler]: " << p_FailedMsg << std::endl;
		return;
	}
	if(p_SuccessMsg)
		std::cerr << p_SuccessMsg << std::endl;
}

#endif // CODE_ARCH_VKEXCEPTIONHANDLER_HPP