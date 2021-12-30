#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vulkan_kernal::instance
{
	VkInstance create(const char* name, const std::vector<const char*>& extensions, void* next);
	void cleanup(VkInstance instance);
}