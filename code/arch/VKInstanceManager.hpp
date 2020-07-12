#ifndef CODE_ARCH_VKINSTANCEMANAGER_HPP
#define CODE_ARCH_VKINSTANCEMANAGER_HPP

#include "GLVK.hpp"
#include "VKDebugManager.hpp"

#include <vector>

class cVKInstanceManager {
  VkInstance m_Instance;
  const static bool m_ValidationSupportFlag;

#ifndef NDEBUG
  cVKDebugManager m_DbgManager;
#endif

public:
  cVKInstanceManager(VkInstanceCreateInfo &);
  ~cVKInstanceManager();

  static bool checkValidationSupport() noexcept;
  static bool checkValidationLayers(const std::vector<const char *> &);

  static std::vector<const char *> getRequiredExtensions();
  
  VkInstance & getInstance() noexcept;
};

#endif