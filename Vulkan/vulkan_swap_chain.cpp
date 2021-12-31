#include "vulkan_swap_chain.h"
#include "vulkan_queue_family.h"
#include "vulkan_settings.h"

#include <stdexcept>
#include <algorithm>

namespace vulkan_kernal::swap_chain
{
	namespace
	{
		VkSurfaceFormatKHR choose_surface_format(const std::vector<VkSurfaceFormatKHR>& surface_formats)
		{
			for (const auto& surface_format : surface_formats)
			{
				if (surface_format.format == VK_FORMAT_B8G8R8A8_SRGB && surface_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				{
					return surface_format;
				}
			}

			return surface_formats.front();
		}

		VkPresentModeKHR choose_present_mode(const std::vector<VkPresentModeKHR>& present_modes)
		{
			for (const VkPresentModeKHR& mode : present_modes)
			{
				if (mode == prefered_present_mode)
				{
					return mode;
				}
			}

			return VK_PRESENT_MODE_FIFO_KHR;
		}

		VkExtent2D choose_extent(const VkSurfaceCapabilitiesKHR& capabilities, const window_interface* window)
		{
			if (capabilities.currentExtent.width != UINT32_MAX)
			{
				return capabilities.currentExtent;
			}

			VkExtent2D extent = window->get_framebuffer_size();
			extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return extent;
		}
	}

	VkSwapchainKHR create(VkPhysicalDevice physical_device, VkDevice logical_device, VkSurfaceKHR surface, const window_interface* window)
	{
		VkSurfaceCapabilitiesKHR capabilities = surface_capabilities(physical_device, surface);
		VkSurfaceFormatKHR surface_format = choose_surface_format(formats(physical_device, surface));
		VkPresentModeKHR present_mode = choose_present_mode(present_modes(physical_device, surface));
		VkExtent2D extent = choose_extent(capabilities, window);

		uint32_t image_count = capabilities.minImageCount + 1;
		if (capabilities.maxImageCount > 0 && image_count > capabilities.maxImageCount)
		{
			image_count = capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		create_info.surface = surface;
		create_info.minImageCount = image_count;
		create_info.imageFormat = surface_format.format;
		create_info.imageColorSpace = surface_format.colorSpace;
		create_info.imageExtent = extent;
		create_info.imageArrayLayers = 1;
		create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		create_info.preTransform = capabilities.currentTransform;
		create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		create_info.presentMode = present_mode;
		create_info.clipped = VK_TRUE;

		uint32_t family_indices[] =
		{
			queue_family::graphics_family(physical_device).value(),
			queue_family::present_family(physical_device, surface).value()
		};

		if (family_indices[0] != family_indices[1])
		{
			create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			create_info.queueFamilyIndexCount = 2;
			create_info.pQueueFamilyIndices = family_indices;
		}
		else
		{
			create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		VkSwapchainKHR swap_chain = nullptr;

		if (vkCreateSwapchainKHR(logical_device, &create_info, nullptr, &swap_chain) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create swap chain!");
		}

		return swap_chain;
	}

	VkSurfaceCapabilitiesKHR surface_capabilities(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		VkSurfaceCapabilitiesKHR capabilities{};
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &capabilities);
		return capabilities;
	}

	std::vector<VkSurfaceFormatKHR> formats(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		std::vector<VkSurfaceFormatKHR> formats;

		if (formatCount != 0)
		{
			formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, formats.data());
		}

		return formats;
	}

	std::vector<VkPresentModeKHR> present_modes(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		uint32_t presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		std::vector<VkPresentModeKHR> modes;

		if (presentModeCount != 0)
		{
			modes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, modes.data());
		}

		return modes;
	}
};