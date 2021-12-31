#include "vulkan_logical_device.h"
#include "vulkan_queue_family.h"
#include "vulkan_settings.h"

#include <set>
#include <vector>
#include <stdexcept>

namespace vulkan_kernal::logical_device
{
	VkDevice create(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		std::set<uint32_t> families =
		{
			queue_family::graphics_family(device).value(),
			queue_family::present_family(device, surface).value()
		};

		for (uint32_t family : families)
		{
			constexpr float priority = 1.0f;
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = family;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &priority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures device_features{};
		device_features.samplerAnisotropy = VK_TRUE;

		VkDeviceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		create_info.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		create_info.pQueueCreateInfos = queueCreateInfos.data();
		create_info.pEnabledFeatures = &device_features;
		create_info.enabledExtensionCount = static_cast<uint32_t>(device::extensions.size());
		create_info.ppEnabledExtensionNames = device::extensions.data();

		if (validation_layers::enabled)
		{
			create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers::names.size());
			create_info.ppEnabledLayerNames = validation_layers::names.data();
		}
		else
		{
			create_info.enabledLayerCount = 0;
		}

		VkDevice logical_device = nullptr;

		if (vkCreateDevice(device, &create_info, nullptr, &logical_device) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create logical device!");
		}

		return logical_device;
	}
}