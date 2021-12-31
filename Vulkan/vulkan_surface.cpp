#include "vulkan_surface.h"

#include <stdexcept>

namespace vulkan_kernal::surface
{
	VkSurfaceKHR create(VkInstance instance, const window_interface* window)
	{
		VkSurfaceKHR surface = window->create_surface(instance);

		if (!surface)
		{
			throw std::runtime_error("failed to create window surface!");
		}

		return surface;
	}
};