#pragma once

#include "window_interface.h"
#include <vulkan/vulkan.h>

namespace vulkan_kernal
{
	namespace swap_chain
	{
		class swap_chain2;
	}

	class vulkan_kernal2
	{
	public:
		vulkan_kernal2(const char* name, const window_interface* window);
		~vulkan_kernal2();

	private:
		void cleanup();

	private:
		VkInstance instance = nullptr;
		VkDebugUtilsMessengerEXT debug_messenger = nullptr;
		VkSurfaceKHR surface = nullptr;
		VkPhysicalDevice physical_device = nullptr;
		VkDevice logical_device = nullptr;
		VkQueue graphics_queue = nullptr;
		VkQueue present_queue = nullptr;
		swap_chain::swap_chain2* swap_chain = nullptr;
	};
}