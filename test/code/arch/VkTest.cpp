#include "test/code/arch/VkTest.hpp"

#include "test/code/arch/Tester.hpp"

int execute_test(int argc, char * argv[]) {

   // If vulkan available.
   if(glfwVulkanSupported()) {
      std::cerr << "GLFW doesn't support Vulkan!" << std::endl;
      std::cerr << "Aborting..." << std::endl;
      abort();
   }

   // Application inf
   VkApplicationInfo appInfo;
   appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
   appInfo.pNext = nullptr;
   appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
   appInfo.pApplicationName = "Vulkan Tester";
   // appInfo.apiVersion = VK_API_VERSION_1_2;
   // appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
   // appInfo.pEngineName = "From Scratch";

   // Vulkan validation layers
   const static std::vector<const char *> validationLayers = {
      "VK_LAYER_KHRONOS_validation" // normal validation
#ifdef ENABLE_VKLAYER_API_DUMP // definition in cmake
      , "VK_LAYER_LUNARG_api_dump"
#endif
      // , "VK_LAYER_LUNARG_standard_validation" // unsupported
   };

   // Vulkan Instance
   if(cVKInstanceManager::checkValidationSupport() && !cVKInstanceManager::checkValidationLayers(validationLayers)) {
      std::cerr << "Vulkan doesn't support following validation layers(" << validationLayers.size() << "):";
      for(const char * const & currentLayer : validationLayers)
         std::cerr << "\t" << currentLayer << std::endl;
      std::cerr << "Aborting..." << std::endl;
      abort();
   }

   const static std::vector<const char *> extensionLayers;

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

   // Vulkan instance manager.
   cVKInstanceManager instcManager(instanceInfo);

   // Enumerate Instance Extensions.
   {
      std::vector<VkExtensionProperties> extensionProperties;

      if(!cVKInstanceManager::checkInstanceExtensions(extensionProperties)) {
         std::cerr << "Failed to find all of Vulkan instance extensions required by GLFW." << std::endl;
         std::cerr << "Aborting..." << std::endl;
         abort();
      }
   }

   // Glfw helper.
   cGLFWHelper glfwHelper;
   glfwHelper.init();

   int mainWM_id = glfwHelper.registerWindow(800, 600, appInfo.pApplicationName);

   while(!glfwWindowShouldClose((GLFWwindow *)glfwHelper.getWindowManager(mainWM_id).getWindow())) {
      glfwPollEvents();

      WAIT_FOR_MS(100);
   }

   return 0;
}