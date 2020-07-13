#ifndef CODE_ARCH_VKEXCEPTIONHANDLER_HPP
#define CODE_ARCH_VKEXCEPTIONHANDLER_HPP

#include <iostream>
#include <vulkan/vulkan.h>

void handleVKResult(const VkResult & p_Result, const char * p_FailedMsg) {
  if(p_Result) {
    std::cerr << "[VKExceptionHandler]: " << p_FailedMsg << std::endl;
    return;
  }
  return;
}

void handleVKResult(const VkResult & p_Result, const char * p_SuccessMsg, const char * p_FailedMsg) {
  if(p_Result) {
    std::cerr << "[VKExceptionHandler]: " << p_FailedMsg << std::endl;
    return;
  }
  std::cerr << p_SuccessMsg << std::endl;
  return;
}

#endif