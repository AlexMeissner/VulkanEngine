#include "vulkan_queue_family.h"

#include <vector>

namespace vulkan_kernal::queue_family
{
	std::optional<uint32_t> graphics_family(VkPhysicalDevice device)
	{
		uint32_t family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &family_count, nullptr);

		std::vector<VkQueueFamilyProperties> families(family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &family_count, families.data());

		for (uint32_t index = 0; index < families.size(); ++index)
		{
			if (families.at(index).queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				return index;
			}
		}

		return std::nullopt;
	}

	std::optional<uint32_t> present_family(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		uint32_t family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &family_count, nullptr);

		std::vector<VkQueueFamilyProperties> families(family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &family_count, families.data());

		for (uint32_t index = 0; index < families.size(); ++index)
		{
			VkBool32 present_support = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, index, surface, &present_support);

			if (present_support)
			{
				return index;
			}
		}

		return std::nullopt;
	}
};