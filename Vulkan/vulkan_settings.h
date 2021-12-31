#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace vulkan_kernal
{
	namespace instance
	{
		extern uint32_t application_version;
		extern const char* engine_name;
		extern uint32_t engine_version;
		extern uint32_t api_version;
		extern VkStructureType instance_type;
		extern VkInstanceCreateFlags flags;
	}

	namespace validation_layers
	{
		extern bool enabled;
		extern std::vector<const char*> names;
		extern VkDebugUtilsMessengerCreateFlagsEXT message_flags;
		extern VkDebugUtilsMessageSeverityFlagsEXT message_severity;
		extern VkDebugUtilsMessageTypeFlagsEXT message_type;
	}

	namespace device
	{
		extern std::vector<const char*> extensions;
	}

	namespace swap_chain
	{
		extern VkPresentModeKHR prefered_present_mode;
	}
}