#ifndef SRC_CODE_ARCH_VKDEBUGMANAGER_HPP
#define SRC_CODE_ARCH_VKDEBUGMANAGER_HPP

#include "src/code/arch/GLVK.hpp"

#include <vulkan/vulkan.h>

#ifndef NDEBUG
#include <iostream>
#define DBG_LOG(ios) std::cout << ios << std::endl
#else
#define DBG_LOG(some_thing) /* some_thing */
#endif // NDEBUG

class cVKDebugManager {
   VkDebugUtilsMessengerEXT m_DebugMessenger;

   static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT *, void *) noexcept;
public:
   void createDebugUtilsMessengerInfo(VkDebugUtilsMessengerCreateInfoEXT &) noexcept;

   VkResult createDebugUtilsMessengerExt(const VkInstance &, const VkDebugUtilsMessengerCreateInfoEXT *, const VkAllocationCallbacks * = nullptr);
   void destroyDebugUtilsMessengerExt(const VkInstance &, const VkAllocationCallbacks * = nullptr);

   VkDebugUtilsMessengerEXT & getDebugUtilsMessenger() noexcept;
};

#endif // SRC_CODE_ARCH_VKDEBUGMANAGER_HPP