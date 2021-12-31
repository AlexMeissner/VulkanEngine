#pragma once

#include "window_interface.h"

#include <vulkan/vulkan.h>
#include <vector>

namespace vulkan_kernal::instance
{
	VkInstance create(const char* name, const window_interface* window);
}