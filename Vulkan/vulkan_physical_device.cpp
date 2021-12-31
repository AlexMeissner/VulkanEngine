#include "vulkan_physical_device.h"
#include "vulkan_queue_family.h"
#include "vulkan_swap_chain.h"
#include "vulkan_settings.h"

#include <set>
#include <vector>
#include <stdexcept>

namespace vulkan_kernal::physical_device
{
	bool supports_extensions(VkPhysicalDevice device)
	{
		uint32_t count = 0;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr);

		std::vector<VkExtensionProperties> available_extensions(count);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &count, available_extensions.data());

		std::set<std::string> required_extensions(device::extensions.begin(), device::extensions.end());

		for (const auto& extension : available_extensions)
		{
			required_extensions.erase(extension.extensionName);
		}

		return required_extensions.empty();
	}

	bool is_valid(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		if (!queue_family::graphics_family(device).has_value() ||
			!queue_family::present_family(device, surface).has_value() ||
			!supports_extensions(device) ||
			swap_chain::formats(device, surface).empty() ||
			swap_chain::present_modes(device, surface).empty())
		{
			return false;
		}

		VkPhysicalDeviceFeatures supportedFeatures;
		vkGetPhysicalDeviceFeatures(device, &supportedFeatures);
		return supportedFeatures.samplerAnisotropy;
	}

	VkPhysicalDevice create(VkInstance instance, VkSurfaceKHR surface)
	{
		uint32_t device_count = 0;
		vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

		if (device_count == 0)
		{
			throw std::runtime_error("failed to find GPUs with Vulkan support");
		}

		std::vector<VkPhysicalDevice> devices(device_count);
		vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

		for (const VkPhysicalDevice& device : devices)
		{
			if (is_valid(device, surface))
			{
				return device;
			}
		}

		throw std::runtime_error("failed to find a suitable GPU");
		return nullptr;
	}

	VkSampleCountFlagBits get_maximal_sample_count(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties physicalDeviceProperties;
		vkGetPhysicalDeviceProperties(device, &physicalDeviceProperties);

		VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
		if (counts & VK_SAMPLE_COUNT_64_BIT) return VK_SAMPLE_COUNT_64_BIT;
		if (counts & VK_SAMPLE_COUNT_32_BIT) return VK_SAMPLE_COUNT_32_BIT;
		if (counts & VK_SAMPLE_COUNT_16_BIT) return VK_SAMPLE_COUNT_16_BIT;
		if (counts & VK_SAMPLE_COUNT_8_BIT) return VK_SAMPLE_COUNT_8_BIT;
		if (counts & VK_SAMPLE_COUNT_4_BIT) return VK_SAMPLE_COUNT_4_BIT;
		if (counts & VK_SAMPLE_COUNT_2_BIT) return VK_SAMPLE_COUNT_2_BIT;
		return VK_SAMPLE_COUNT_1_BIT;
	}
}