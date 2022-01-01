#pragma once

#include "window_interface.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace vulkan_kernal::swap_chain
{
	VkSurfaceCapabilitiesKHR surface_capabilities(VkPhysicalDevice device, VkSurfaceKHR surface);
	std::vector<VkSurfaceFormatKHR> formats(VkPhysicalDevice device, VkSurfaceKHR surface);
	std::vector<VkPresentModeKHR> present_modes(VkPhysicalDevice device, VkSurfaceKHR surface);

	class swap_chain2
	{
	public:
		void create(VkPhysicalDevice physical_device, VkDevice logical_device, VkSurfaceKHR surface, const window_interface* window);
		void cleanup(VkDevice logical_device);

		VkExtent2D get_extent() const;
		VkFormat get_format() const;

	private:
		VkSwapchainKHR swap_chain = nullptr;
		std::vector<VkImage> images;
		std::vector<VkImageView> image_views;
		VkSurfaceFormatKHR surface_format{};
		VkExtent2D extent{};
	};
};