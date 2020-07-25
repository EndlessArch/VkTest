#ifndef CODE_ARCH_VKDEBUGMANAGER_HPP
#define CODE_ARCH_VKDEBUGMANAGER_HPP

#include "code/arch/GLVK.hpp"

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

	VkResult createDebugUtilsMessengerExt(const VkInstance &, const VkDebugUtilsMessengerCreateInfoEXT *, const VkAllocationCallbacks *);
	void destroyDebugUtilsMessengerExt(const VkInstance &, const VkAllocationCallbacks *);

	VkDebugUtilsMessengerEXT & getDebugUtilsMessenger() noexcept;
};

#endif // CODE_ARCH_VKDEBUGMANAGER_HPP