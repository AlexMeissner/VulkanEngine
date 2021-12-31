#pragma once

#include <stdint.h>
#include <optional>
#include <vulkan/vulkan.h>

namespace vulkan_kernal::physical_device
{
	VkPhysicalDevice create(VkInstance instance, VkSurfaceKHR surface);
	VkSampleCountFlagBits get_maximal_sample_count(VkPhysicalDevice device);
}