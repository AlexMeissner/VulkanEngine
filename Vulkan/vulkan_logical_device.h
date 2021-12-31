#pragma once

#include <vulkan/vulkan.h>

namespace vulkan_kernal::logical_device
{
	VkDevice create(VkPhysicalDevice device, VkSurfaceKHR surface);
}