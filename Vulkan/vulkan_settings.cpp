#include "vulkan_settings.h"

namespace vulkan_kernal
{
	namespace instance
	{
		VkStructureType application_type = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		uint32_t application_version = VK_MAKE_VERSION(1, 0, 0);
		const char* engine_name = "No Engine";
		uint32_t engine_version = VK_MAKE_VERSION(1, 0, 0);
		uint32_t api_version = VK_API_VERSION_1_0;

		VkStructureType instance_type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		VkInstanceCreateFlags flags = 0;
	}

	namespace validation_layers
	{
#ifdef NDEBUG
		bool enabled = false;
#else
		bool enabled = true;
#endif
		std::vector<const char*> names = { "VK_LAYER_KHRONOS_validation" };
		VkStructureType type = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		VkDebugUtilsMessengerCreateFlagsEXT message_flags = 0;
		VkDebugUtilsMessageSeverityFlagsEXT message_severity = /*VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |*/ VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;;
		VkDebugUtilsMessageTypeFlagsEXT message_type = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	}
}