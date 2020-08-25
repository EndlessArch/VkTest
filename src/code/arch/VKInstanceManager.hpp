#ifndef SRC_CODE_ARCH_VKINSTANCEMANAGER_HPP
#define SRC_CODE_ARCH_VKINSTANCEMANAGER_HPP

#include "src/code/arch/GLVK.hpp"
#include "src/code/arch/VKDebugManager.hpp"

#include <vector>

class cVKInstanceManager {
   VkInstance m_Instance;

   static constexpr inline bool m_ValidationSupportFlag = 
#ifndef NDEBUG
true;

   cVKDebugManager m_DbgManager;
#else
false;
#endif

public:
   cVKInstanceManager(VkInstanceCreateInfo &);
   ~cVKInstanceManager();

   static auto checkValidationSupport() noexcept -> decltype(m_ValidationSupportFlag);
   // static constexpr bool checkValidationSupport() noexcept;
   static bool checkValidationLayers(const std::vector<const char *> &);

   static bool checkInstanceExtensions(std::vector<VkExtensionProperties> &);
   // static std::vector<const char *> && getRequiredExtensions();
   
   VkInstance & getInstance() noexcept;
};

// instance string returner
#define LAMBDA_INSTANCE_STRING_RETURNER ([](const char * p_T) -> const char * { \
   return p_T; \
})

// #include <type_traits>

// Check if vector1 contains vector2
struct ListChecker {
   bool value;
#define LC_NOEXCEPT /*noexcept*/ //_NOEXCEPT // stl
   template <typename _Tp, typename _Func>
   void operator()(  const std::vector<_Tp> &, const std::vector<const char *> &,
                     const _Func) LC_NOEXCEPT;

   template <typename _Tp, typename _Func>
   void operator()(  const std::vector<const char *> &, const std::vector<_Tp> &,
                     const _Func) LC_NOEXCEPT;

   // when two containers's types are same.
   template <typename _Tp, typename _Func>
   void operator()(  const std::vector<_Tp> &, const std::vector<_Tp> &,
                     const _Func) LC_NOEXCEPT;

   template <typename _Tp1, typename _Tp2 = _Tp1, typename _Func1, typename _Func2 = _Func1>
   void operator()(  const std::vector<_Tp1> &, const std::vector<_Tp2> &,
                     const _Func1, const _Func2) LC_NOEXCEPT;
};

#endif // SRC_CODE_ARCH_VKINSTANCEMANAGER_HPP