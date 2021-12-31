#pragma once

#include <vulkan/vulkan.h>
#include "window_interface.h"

namespace vulkan_kernal::surface
{
	VkSurfaceKHR create(VkInstance instance, const window_interface* window);
};