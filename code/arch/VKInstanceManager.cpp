#include "VKInstanceManager.hpp"

#include "VKExceptionHandler.hpp"

#include <memory>

cVKInstanceManager::cVKInstanceManager(VkInstanceCreateInfo & p_InstcInfo) {
  p_InstcInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  p_InstcInfo.flags = 0; // NOTE: Error comes if flags != 0(could be prevented with VkInstanceCreateInfo = {}), just validating.
  p_InstcInfo.pNext = nullptr;

  // TODO: Find out some other ways to call them.
  // auto & rAppInfo = const_cast<VkApplicationInfo *>(p_InstcInfo.pApplicationInfo);
  // VkApplicationInfo *& someAppInfo = const_cast<VkApplicationInfo *>(p_InstcInfo.pApplicationInfo);

  const_cast<VkApplicationInfo *>(p_InstcInfo.pApplicationInfo)->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  const_cast<VkApplicationInfo *>(p_InstcInfo.pApplicationInfo)->pNext = nullptr;
  const_cast<VkApplicationInfo *>(p_InstcInfo.pApplicationInfo)->apiVersion = VK_API_VERSION_1_2; // VK_MAKE_VERSION(1, 2, 135); // = 1.2.135
  const_cast<VkApplicationInfo *>(p_InstcInfo.pApplicationInfo)->engineVersion = VK_MAKE_VERSION(1, 0, 0);
  const_cast<VkApplicationInfo *>(p_InstcInfo.pApplicationInfo)->pEngineName = "From Scratch";

#ifndef NDEBUG // this->m_DbgManager
    VkDebugUtilsMessengerCreateInfoEXT dbgCreateInfo;
    this->m_DbgManager.createDebugUtilsMessengerInfo(dbgCreateInfo);
    p_InstcInfo.pNext = &dbgCreateInfo;
#endif
  VkResult res = vkCreateInstance((VkInstanceCreateInfo *)&p_InstcInfo, nullptr, &this->m_Instance);
  handleVKResult(res, "Created Vulkan instance.", "Failed to create Vulkan instance.");
#ifndef NDEBUG
    res = this->m_DbgManager.createDebugUtilsMessengerExt((const VkInstance &)this->m_Instance,
                                                          (const VkDebugUtilsMessengerCreateInfoEXT *)&dbgCreateInfo,
                                                          (const VkAllocationCallbacks *)nullptr);
    handleVKResult(res, "Created Vulkan debug messenger.", "Failed to create Vulkan debug messenger.");
#endif
}

cVKInstanceManager::~cVKInstanceManager() {
  // All child objects should be destroyed first.
#ifndef NDEBUG
  this->m_DbgManager.destroyDebugUtilsMessengerExt((const VkInstance &)this->m_Instance, (const VkAllocationCallbacks *)nullptr);
#endif
  vkDestroyInstance(this->m_Instance, nullptr);
}

const bool cVKInstanceManager::m_ValidationSupportFlag =
#ifndef NDEBUG
true;
#else
false;
#endif

bool cVKInstanceManager::checkValidationSupport() noexcept {
  return m_ValidationSupportFlag; 
}

bool cVKInstanceManager::checkValidationLayers(const std::vector<const char *> & validationLayers) {
  uint32_t availableLayerCnt = 0;
  VkResult res = vkEnumerateInstanceLayerProperties(&availableLayerCnt, nullptr);
  handleVKResult(res, "Failed to enumerate the number of Vulkan instance layers.");

  std::vector<VkLayerProperties> availableLayers(availableLayerCnt);
  res = vkEnumerateInstanceLayerProperties(&availableLayerCnt, &*availableLayers.begin());
  handleVKResult(res, "Failed to enumerate Vulkan instance layers.");

  bool resultFlag = true, totalFlag;
  for(const char * const validationLyr : validationLayers) {
    totalFlag = false;
    if(std::any_of(availableLayers.begin(), availableLayers.end(), [&validationLyr](const VkLayerProperties & p_LyrPrp) -> bool {
      return !strcmp(validationLyr, p_LyrPrp.layerName); // ==
    })) totalFlag = true;
    resultFlag &= totalFlag;
  }

  std::cerr << "Found " << availableLayerCnt << " available validation layers." << std::endl;
  for(const VkLayerProperties & currentLyrPrp : availableLayers)
    std::cerr << "\t" << currentLyrPrp.layerName << std::endl;

  return resultFlag;
}

std::vector<const char *> cVKInstanceManager::getRequiredExtensions() {
  uint32_t glfwExtensionCnt = 0;
  const char ** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCnt);

  std::vector<const char *> requiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCnt);

  if(checkValidationSupport())
    requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

  return requiredExtensions;
}

VkInstance & cVKInstanceManager::getInstance() noexcept {
  return this->m_Instance;
}