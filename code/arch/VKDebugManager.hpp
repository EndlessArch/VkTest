#ifndef CODE_ARCH_VKDEBUGMANAGER_HPP
#define CODE_ARCH_VKDEBUGMANAGER_HPP

#include "GLVK.hpp"

#ifndef NDEBUG
#include <iostream>
#define DBG_LOG(ios_str) std::cout << (ios_str) << std::endl
#else
#define DBG_LOG(some_thing)
#endif

class cVKDebugManager {
  VkDebugUtilsMessengerEXT m_DebugMessenger;

  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT*, void*) noexcept;
public:
  void createDebugUtilsMessengerInfo(VkDebugUtilsMessengerCreateInfoEXT &) noexcept;

  VkResult createDebugUtilsMessengerExt(const VkInstance &, const VkDebugUtilsMessengerCreateInfoEXT *, const VkAllocationCallbacks *);
  void destroyDebugUtilsMessengerExt(const VkInstance &, const VkAllocationCallbacks *);

  VkDebugUtilsMessengerEXT & getDebugUtilsMessenger() noexcept;
};

#endif