#pragma once

#include "window_interface.h"
#include <vulkan/vulkan.h>

namespace vulkan_kernal
{
	class vulkan_kernal2
	{
	public:
		vulkan_kernal2(const char* name, const window_interface* window);
		~vulkan_kernal2();

	private:
		void cleanup();
		void cleanup_swap_chain();

	private:
		VkInstance instance = nullptr;
		VkDebugUtilsMessengerEXT debug_messenger = nullptr;
		VkSurfaceKHR surface = nullptr;
		VkPhysicalDevice physical_device = nullptr;
		VkDevice logical_device = nullptr;
		VkQueue graphics_queue = nullptr;
		VkQueue present_queue = nullptr;
		VkSwapchainKHR swap_chain = nullptr;
	};
}