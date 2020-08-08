#include "src/code/arch/VKDebugManager.hpp"

#include <iostream>

// #define handleCallback(p_CallbackResult)  if(!p_CallbackResult) { \
//                                             std::cerr << "Failed to initialize " << #p_CallbackResult << ".\nAborting..." << std::endl; \
//                                             abort();\
//                                           }

static uint32_t __vkDbgCb_err_cnt = 0;

VkBool32 cVKDebugManager::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT p_MsgSeverity, VkDebugUtilsMessageTypeFlagsEXT p_MsgType, const VkDebugUtilsMessengerCallbackDataEXT * p_CallbackData, void * p_UserData) noexcept {
   std::cerr << "[Validation Layer Callback Message](" << ++__vkDbgCb_err_cnt << "): " << p_CallbackData->pMessage << std::endl;
   return VK_FALSE;
}

void cVKDebugManager::createDebugUtilsMessengerInfo(VkDebugUtilsMessengerCreateInfoEXT & p_MsgCreateInfo) noexcept {
   p_MsgCreateInfo = {};
   p_MsgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
   // verbose & warning & error
   p_MsgCreateInfo.messageSeverity  =  VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
   // general & validation & performance
   p_MsgCreateInfo.messageType      =  VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT     |
                                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT  |
                                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
   p_MsgCreateInfo.pfnUserCallback = cVKDebugManager::debugCallback;
   return;
}

VkResult cVKDebugManager::createDebugUtilsMessengerExt(  const VkInstance & p_Instc,
                                                         const VkDebugUtilsMessengerCreateInfoEXT * p_DebugUtilsCreateInf,
                                                         const VkAllocationCallbacks * p_AllocCB) {
   auto funcCreateDebugUtilsMessenger = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr((VkInstance)p_Instc, "vkCreateDebugUtilsMessengerEXT");
   if(!funcCreateDebugUtilsMessenger) return VK_ERROR_EXTENSION_NOT_PRESENT;
   return funcCreateDebugUtilsMessenger((VkInstance)p_Instc, p_DebugUtilsCreateInf, p_AllocCB, &this->m_DebugMessenger);
}

void cVKDebugManager::destroyDebugUtilsMessengerExt(  const VkInstance & p_Instc,
                                                      const VkAllocationCallbacks * p_AllocCB) {
   auto funcDestroyDebugUtilsMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr((VkInstance)p_Instc, "vkDestroyDebugUtilsMessengerEXT");
   if(!funcDestroyDebugUtilsMessenger) return;
   funcDestroyDebugUtilsMessenger((VkInstance)p_Instc, this->m_DebugMessenger, p_AllocCB);
}

VkDebugUtilsMessengerEXT & cVKDebugManager::getDebugUtilsMessenger() noexcept {
   return this->m_DebugMessenger;
}