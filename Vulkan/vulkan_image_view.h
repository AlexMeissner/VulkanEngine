#pragma once

#include <vulkan/vulkan.h>

namespace vulkan_kernal::image_view
{
	VkImageView create(VkDevice device, VkImage image, VkImageViewType type, VkFormat format, VkImageAspectFlags aspect_flags, uint32_t level_count);
}