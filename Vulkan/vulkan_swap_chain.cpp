#include "vulkan_swap_chain.h"

namespace vulkan_kernal::swap_chain
{
	VkSurfaceCapabilitiesKHR surface_capabilities(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		VkSurfaceCapabilitiesKHR capabilities{};
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &capabilities);
		return capabilities;
	}

	std::vector<VkSurfaceFormatKHR> formats(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		std::vector<VkSurfaceFormatKHR> formats;

		if (formatCount != 0)
		{
			formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, formats.data());
		}

		return formats;
	}

	std::vector<VkPresentModeKHR> present_modes(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		uint32_t presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		std::vector<VkPresentModeKHR> modes;

		if (presentModeCount != 0)
		{
			modes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, modes.data());
		}

		return modes;
	}
};