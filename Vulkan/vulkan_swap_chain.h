#pragma once

#include "window_interface.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace vulkan_kernal::swap_chain
{
	VkSwapchainKHR create(VkPhysicalDevice physical_device, VkDevice logical_device, VkSurfaceKHR surface, const window_interface* window);
	VkSurfaceCapabilitiesKHR surface_capabilities(VkPhysicalDevice device, VkSurfaceKHR surface);
	std::vector<VkSurfaceFormatKHR> formats(VkPhysicalDevice device, VkSurfaceKHR surface);
	std::vector<VkPresentModeKHR> present_modes(VkPhysicalDevice device, VkSurfaceKHR surface);
};