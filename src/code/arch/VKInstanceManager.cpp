#include "src/code/arch/VKInstanceManager.hpp"

#include "src/code/arch/VKExceptionHandler.hpp"

// You can define 'VSCODE_LINTER' at editor|linter level.
// this won't affect codes in compile-time,
#ifdef VSCODE_LINTER
#define DONT_COMPILE(expression_) expression_
#else
#define DONT_COMPILE(expression_) /*nothing*/
#endif

// Stupid linter shows errors.
// NOTE: default parameter cannot be redefined.
extern void handleGLFWResult(bool, const char *, const char * DONT_COMPILE(= nullptr)) noexcept;
extern void handleVKResult(const VkResult &, const char *, const char * DONT_COMPILE(= nullptr)) noexcept;

#include <memory>

cVKInstanceManager::cVKInstanceManager(VkInstanceCreateInfo & p_InstcInfo) {
   p_InstcInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
   p_InstcInfo.flags = 0; // NOTE: Error comes if flags != 0(could be prevented with VkInstanceCreateInfo = {}), just validating.
   p_InstcInfo.pNext = nullptr;

#define APPLICATION_INF_PTR(P_INSTC) const_cast<VkApplicationInfo *>(P_INSTC.pApplicationInfo)
#define GET_INSTC_INF(get_) APPLICATION_INF_PTR(p_InstcInfo)->get_ // simplify.
   GET_INSTC_INF(sType) = VK_STRUCTURE_TYPE_APPLICATION_INFO;
   GET_INSTC_INF(pNext) = nullptr;
   GET_INSTC_INF(apiVersion) = VK_API_VERSION_1_2; // VK_MAKE_VERSION(1, 2, 135); // = 1.2.135
   GET_INSTC_INF(engineVersion) = VK_MAKE_VERSION(1, 0, 0);
   GET_INSTC_INF(pEngineName) = "From Scratch";

#undef GET_INSTC_INF
#undef APPLICATION_INF_PTR //

#ifndef NDEBUG // this->m_DbgManager
      VkDebugUtilsMessengerCreateInfoEXT dbgCreateInfo;
      this->m_DbgManager.createDebugUtilsMessengerInfo(dbgCreateInfo);
      p_InstcInfo.pNext = &dbgCreateInfo;
#endif
   VkResult res = vkCreateInstance((VkInstanceCreateInfo *)&p_InstcInfo, nullptr, &this->m_Instance);
   handleVKResult(res, "Failed to create Vulkan instance object.", "Created Vulkan instance object.");
#ifndef NDEBUG
      res = this->m_DbgManager.createDebugUtilsMessengerExt((const VkInstance &)this->m_Instance,
                                                            (const VkDebugUtilsMessengerCreateInfoEXT *)&dbgCreateInfo);
      handleVKResult(res, "Failed to create Vulkan debug messenger.", "Created Vulkan debug messenger.");
#endif
}

cVKInstanceManager::~cVKInstanceManager() {
   // All child objects should be destroyed first.
#ifndef NDEBUG
   this->m_DbgManager.destroyDebugUtilsMessengerExt((const VkInstance &)this->m_Instance);
#endif
   vkDestroyInstance(this->m_Instance, nullptr);

   std::cout << "Destroyed Vulkan instance object." << std::endl;

   ////
   std::cout << "Press enter to continue...";
   std::cin.get();
}

constexpr inline bool cVKInstanceManager::m_ValidationSupportFlag;

auto cVKInstanceManager::checkValidationSupport() noexcept -> decltype(m_ValidationSupportFlag) {
// constexpr bool cVKInstanceManager::checkValidationSupport() noexcept {
   return m_ValidationSupportFlag;
}

bool cVKInstanceManager::checkValidationLayers(const std::vector<const char *> & validationLayers) {
   uint32_t availableLayerCnt = 0;
   VkResult res = vkEnumerateInstanceLayerProperties(&availableLayerCnt, nullptr);
   handleVKResult(res, "Failed to enumerate the number of Vulkan instance layers.");

   std::vector<VkLayerProperties> availableLayers(availableLayerCnt);
   res = vkEnumerateInstanceLayerProperties(&availableLayerCnt, &*availableLayers.begin());
   handleVKResult(res, "Failed to enumerate Vulkan instance layers.");

   ListChecker lyrChecker;
   lyrChecker( availableLayers, validationLayers,
               std::move([](const VkLayerProperties & p_t2) -> const char * {
                  return p_t2.layerName;
               }));

   std::cerr << "Found " << availableLayerCnt << " available validation layer" << (availableLayerCnt < 2 ? "." : "s.") << std::endl;
   for(const VkLayerProperties & currentLyrPrp : availableLayers)
      std::cerr << "\t" << currentLyrPrp.layerName << std::endl;

   return lyrChecker.value;
}

bool cVKInstanceManager::checkInstanceExtensions(std::vector<VkExtensionProperties> & p_ExtPropsStore) {
   uint32_t glfwRequiredVkInstanceExtensionCnt = 0;
   const char ** glfwRequiredVkInstanceExtensions = glfwGetRequiredInstanceExtensions(&glfwRequiredVkInstanceExtensionCnt);

   handleGLFWResult( std::any_of(glfwRequiredVkInstanceExtensions,
                                 glfwRequiredVkInstanceExtensions + glfwRequiredVkInstanceExtensionCnt,
                                 std::move([](const char * p_ExtName) -> bool {
                                    return !strcmp(VK_KHR_SURFACE_EXTENSION_NAME, p_ExtName);
                                 })),
                     "Failed to get Vulkan instance extensions required by GLFW.");

   std::vector<const char *> requiredVkInstanceExtensions(  glfwRequiredVkInstanceExtensions,
                                                            glfwRequiredVkInstanceExtensions + glfwRequiredVkInstanceExtensionCnt);

   if(checkValidationSupport()) {
      ++glfwRequiredVkInstanceExtensionCnt;
      requiredVkInstanceExtensions.push_back(std::move(VK_EXT_DEBUG_UTILS_EXTENSION_NAME));
   }

   std::cerr << glfwRequiredVkInstanceExtensionCnt << " extension" << (glfwRequiredVkInstanceExtensionCnt < 2 ? " is" : "s are") << " required by GLFW." << std::endl;
   for(const char * requiredVkExt : requiredVkInstanceExtensions)
      std::cerr << "\t" << requiredVkExt << std::endl;

   uint32_t extensionCnt = 0;
   VkResult res;
   res = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCnt, nullptr);
   handleVKResult(res, "Failed to enumerate the number of Vulkan instance extensions.");
   std::vector<VkExtensionProperties> extensionProperties(extensionCnt);
   res = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCnt, extensionProperties.data());
   handleVKResult(res, "Failed to enumerate Vulkan instance extensions.");

   ListChecker extPropsChecker;
   extPropsChecker(  extensionProperties, requiredVkInstanceExtensions,
                     std::move([](const VkExtensionProperties & p_t1) -> const char * {
                        return p_t1.extensionName;
                     }));

   std::cerr << "Found " << extensionProperties.size() << " avilable extensions." << std::endl;
   for(const VkExtensionProperties & currentExtProp : extensionProperties)
      std::cerr << "\t" << currentExtProp.extensionName << "(v:" << currentExtProp.specVersion << ")" << std::endl;

   if(extPropsChecker.value)
      p_ExtPropsStore = std::move(extensionProperties);

   return extPropsChecker.value;
}

// std::vector<const char *> && cVKInstanceManager::getRequiredExtensions() {
//   uint32_t glfwExtensionCnt = 0;
//   const char ** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCnt);

//   std::vector<const char *> requiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCnt);

//   if(checkValidationSupport())
//     requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

//   std::cerr << "Found " << (glfwExtensionCnt + 1) << " required extensions." << std::endl;
//   for(const char * const extensionName : requiredExtensions)
//     std::cerr << "\t" << extensionName << std::endl;

//   return std::move(requiredExtensions);
// }

VkInstance & cVKInstanceManager::getInstance() noexcept {
   return this->m_Instance;
}

template <typename _Tp, typename _Func>
void ListChecker::operator()( const std::vector<_Tp> & p_Cont1, const std::vector<const char *> & p_Cont2,
                              const _Func p_Func) LC_NOEXCEPT {
   ;
   this->operator()(p_Cont1, p_Cont2, std::move(p_Func), std::move(LAMBDA_INSTANCE_STRING_RETURNER));
}

template <typename _Tp, typename _Func>
void ListChecker::operator()( const std::vector<const char *> & p_Cont1, const std::vector<_Tp> & p_Cont2,
                              const _Func p_Func) LC_NOEXCEPT {
   ;
   this->operator()(p_Cont1, p_Cont2, std::move(LAMBDA_INSTANCE_STRING_RETURNER), std::move(p_Func));
}

template <typename _Tp, typename _Func>
void ListChecker::operator()( const std::vector<_Tp> & p_Cont1, const std::vector<_Tp> & p_Cont2,
                              const _Func p_Func) LC_NOEXCEPT {
   ;
   this->operator()<_Tp, _Func &&>(p_Cont1, p_Cont2, std::move(p_Func), std::move(p_Func));
}

template <typename _Tp1, typename _Tp2, typename _Func1, typename _Func2>
void ListChecker::operator()( const std::vector<_Tp1> & p_Cont1, const std::vector<_Tp2> & p_Cont2,
                              const _Func1 p__Func1, const _Func2 p__Func2) LC_NOEXCEPT {
   ;
   this->value = std::all_of(p_Cont2.begin(), p_Cont2.end(),
      std::move([&p_Cont1, &p__Func1, &p__Func2](const _Tp2 & p_E2) -> bool {
         return std::any_of(  p_Cont1.begin(), p_Cont1.end(),
                              std::move([&p_E2, &p__Func1, &p__Func2](const _Tp1 & p_E1) -> bool {
                                 return !strcmp(p__Func1(p_E1), p__Func2(p_E2));
                              }));
   }));
   return;
}