#include <iostream>
#include <vector>
#ifndef NDEBUG
#include <execinfo.h>
void __SIGSEVHANDLER(int SIG) {
  void * arr[40]; // remind it's on stack mem.
  size_t arr_size = backtrace(arr, (sizeof(arr) / sizeof(arr[0])));
  std::cerr << "Signal: " << SIG << "." << std::endl;
  backtrace_symbols_fd(arr, arr_size, 0);
  exit(SIG);
}
#endif

#include "code/arch/Helper.hpp"

int main(int argc, char * argv[]) {
  std::ios_base::sync_with_stdio(false);
#ifndef NDEBUG
  signal(SIGSEGV, __SIGSEVHANDLER);
#endif
  if(glfwVulkanSupported()) {
    std::cerr << "GLFW doesn't support Vulkan!" << std::endl;
    std::cerr << "Aborting..." << std::endl;
    abort();
  }

  VkApplicationInfo appInfo;
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pNext = nullptr;
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pApplicationName = "Vulkan Tester";
  // appInfo.apiVersion = VK_API_VERSION_1_2;
  // appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  // appInfo.pEngineName = "From Scratch";

  const static std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation" // normal validation
    // , "VK_LAYER_LUNARG_api_dump" // sth more specific
    // , "VK_LAYER_LUNARG_standard_validation" // unsupported
  };

  // Vulkan instance layers
  if(cVKInstanceManager::checkValidationSupport() && !cVKInstanceManager::checkValidationLayers(validationLayers)) {
    std::cerr << "Vulkan doesn't support following validation layers(" << validationLayers.size() << "):";
    for(const char * currentLayer : validationLayers)
      std::cerr << "\t" << currentLayer << std::endl;
    std::cerr << "Aborting..." << std::endl;
    abort();
  }

  const static std::vector<const char *> extensionLayers = cVKInstanceManager::getRequiredExtensions();

  VkInstanceCreateInfo instanceInfo {};
  instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instanceInfo.pNext = nullptr;
  instanceInfo.pApplicationInfo = (const VkApplicationInfo *)&appInfo;
  if(cVKInstanceManager::checkValidationSupport()) {
    instanceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    instanceInfo.ppEnabledLayerNames = validationLayers.data();
  } else {
    instanceInfo.enabledLayerCount = static_cast<uint32_t>(0);
    instanceInfo.ppEnabledLayerNames = nullptr;
  }
  instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensionLayers.size());
  instanceInfo.ppEnabledExtensionNames = extensionLayers.data();

  // FIXME: SEGFAULT
  cVKInstanceManager instcManager(instanceInfo);

  // Enumerate Instance Extensions.
  uint32_t extensionCnt = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCnt, nullptr);
  std::vector<VkExtensionProperties> extensionProperties(extensionCnt);
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCnt, extensionProperties.data());

  std::cout << "Found " << extensionCnt << " available extensions." << std::endl;
  for(VkExtensionProperties currentExtensionProp : extensionProperties)
    std::cout << '\t' << currentExtensionProp.extensionName << " (" << currentExtensionProp.specVersion << ')' << std::endl;

  cGLFWHelper glfwHelper; // init glfw
  glfwHelper.init();

  int mainWM_id = glfwHelper.registerWindow(800, 600, appInfo.pApplicationName);

  while(!glfwWindowShouldClose((GLFWwindow *)glfwHelper.getWindowManager(mainWM_id).getWindow())) {
    glfwPollEvents();
  }

  ;

  return 0;
}