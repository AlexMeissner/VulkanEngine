#pragma once

#include <vulkan/vulkan.h>

namespace vulkan_kernal::validation_layers
{
	VkDebugUtilsMessengerCreateInfoEXT generate_create_info();
	VkDebugUtilsMessengerEXT create(VkInstance instance);
	void cleanup(VkInstance instance, VkDebugUtilsMessengerEXT messenger);
	bool available();
}