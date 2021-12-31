#pragma once

#include <optional>
#include <vulkan/vulkan.h>

namespace vulkan_kernal::queue_family
{
	std::optional<uint32_t> graphics_family(VkPhysicalDevice device);
	std::optional<uint32_t> present_family(VkPhysicalDevice device, VkSurfaceKHR surface);
};