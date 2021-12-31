#include "vulkan_kernal.h"
#include "vulkan_instance.h"
#include "validation.h"
#include "vulkan_surface.h"
#include "vulkan_settings.h"
#include "vulkan_swap_chain.h"
#include "vulkan_queue_family.h"
#include "vulkan_logical_device.h"
#include "vulkan_physical_device.h"

namespace vulkan_kernal
{
	vulkan_kernal2::vulkan_kernal2(const char* name, const window_interface* window)
	{
		instance = instance::create(name, window);
		debug_messenger = validation_layers::create(instance);
		surface = surface::create(instance, window);
		physical_device = physical_device::create(instance, surface);
		logical_device = logical_device::create(physical_device, surface);

		vkGetDeviceQueue(logical_device, queue_family::graphics_family(physical_device).value(), 0, &graphics_queue);
		vkGetDeviceQueue(logical_device, queue_family::present_family(physical_device, surface).value(), 0, &present_queue);

		swap_chain = swap_chain::create(physical_device, logical_device, surface, window);
	}

	vulkan_kernal2::~vulkan_kernal2()
	{
		cleanup();
	}

	void vulkan_kernal2::cleanup()
	{
		cleanup_swap_chain();
		vkDestroyDevice(logical_device, nullptr);
		validation_layers::cleanup(instance, debug_messenger);
		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);
	}

	void vulkan_kernal2::cleanup_swap_chain()
	{
		vkDestroySwapchainKHR(logical_device, swap_chain, nullptr);
	}
}