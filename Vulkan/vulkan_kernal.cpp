#include "vulkan_kernal.h"
#include "instance.h"
#include "validation.h"
#include "vulkan_settings.h"

namespace vulkan_kernal
{
	vulkan_kernal2::vulkan_kernal2(const char* name, const window_interface* window)
	{
		void* validation_layer_create_info = nullptr;
		std::vector<const char*> extensions = window->get_extensions();

		if (validation_layers::enabled && validation_layers::available())
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			const auto create_info = validation_layers::generate_create_info();
			validation_layer_create_info = (VkDebugUtilsMessengerCreateInfoEXT*)&create_info;
		}

		instance = instance::create(name, extensions, validation_layer_create_info);
		debug_messenger = validation_layers::create(instance);
	}

	vulkan_kernal2::~vulkan_kernal2()
	{
		cleanup();
	}

	void vulkan_kernal2::cleanup()
	{
		cleanup_swap_chain();
		validation_layers::cleanup(instance, debug_messenger);
		instance::cleanup(instance);
	}

	void vulkan_kernal2::cleanup_swap_chain()
	{
	}
}