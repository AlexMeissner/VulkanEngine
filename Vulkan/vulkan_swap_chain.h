#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace vulkan_kernal::swap_chain
{
	VkSurfaceCapabilitiesKHR surface_capabilities(VkPhysicalDevice device, VkSurfaceKHR surface);
	std::vector<VkSurfaceFormatKHR> formats(VkPhysicalDevice device, VkSurfaceKHR surface);
	std::vector<VkPresentModeKHR> present_modes(VkPhysicalDevice device, VkSurfaceKHR surface);
};