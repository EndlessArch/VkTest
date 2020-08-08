#ifndef CODE_ARCH_VKEXCEPTIONHANDLER_HPP
#define CODE_ARCH_VKEXCEPTIONHANDLER_HPP

#include <iostream>
#include <vulkan/vulkan.h>

void handleGLFWResult(bool p_ResultFlag, const char * p_FailedMsg, const char * p_SuccessMsg = nullptr) noexcept;

void handleVKResult(const VkResult & p_Result, const char * p_FailedMsg, const char * p_SuccessMsg = nullptr) noexcept;

#endif // CODE_ARCH_VKEXCEPTIONHANDLER_HPP