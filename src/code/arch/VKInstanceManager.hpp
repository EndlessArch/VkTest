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

	static bool checkInstanceExtensions(std::vector<VkExtensionProperties> &);
	// static std::vector<const char *> && getRequiredExtensions();
	
	VkInstance & getInstance() noexcept;
};

// instance string returner
#define LAMBDA_INSTANCE_STRING_RETURNER ([](const char * p_T) -> const char * { \
	return p_T; \
})

// Check if vector1 contains vector2
struct ListChecker {
	bool value;
#define LC_NOEXCEPT /*noexcept*/
	template <typename _Tp, typename _Func>
	void operator()(const std::vector<_Tp> &, const std::vector<const char *> &,
									const _Func &&) LC_NOEXCEPT;

	template <typename _Tp, typename _Func>
	void operator()(const std::vector<const char *> &, const std::vector<_Tp> &,
									const _Func &&) LC_NOEXCEPT;

	// when two containers's types are same.
	template <typename _Tp, typename _Func>
	void operator()(const std::vector<_Tp> &, const std::vector<_Tp> &,
									const _Func &&) LC_NOEXCEPT;

	template <typename _Tp1, typename _Tp2 = _Tp1,
						typename _Func1, typename _Func2 = _Func1>
	void operator()(const std::vector<_Tp1> &, const std::vector<_Tp2> &,
									const _Func1 &&, const _Func2 &&) LC_NOEXCEPT;
};

#endif // CODE_ARCH_VKINSTANCEMANAGER_HPP