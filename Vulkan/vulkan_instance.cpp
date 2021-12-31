#include "vulkan_instance.h"
#include "validation.h"
#include "vulkan_settings.h"

#include <stdexcept>

namespace vulkan_kernal::instance
{
	VkInstance create(const char* name, const window_interface* window)
	{
		void* next = nullptr;
		std::vector<const char*> extensions = window->get_extensions();

		if (validation_layers::enabled && validation_layers::available())
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			const auto create_info = validation_layers::generate_create_info();
			next = (VkDebugUtilsMessengerCreateInfoEXT*)&create_info;
		}

		VkApplicationInfo app_info{};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pNext = nullptr;
		app_info.pApplicationName = name;
		app_info.applicationVersion = application_version;
		app_info.pEngineName = engine_name;
		app_info.engineVersion = engine_version;
		app_info.apiVersion = api_version;

		VkInstanceCreateInfo create_info{};
		create_info.sType = instance_type;
		create_info.pNext = next;
		create_info.flags = flags;
		create_info.pApplicationInfo = &app_info;
		create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers::names.size());
		create_info.ppEnabledLayerNames = validation_layers::names.data();
		create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		create_info.ppEnabledExtensionNames = extensions.data();

		VkInstance instance = nullptr;

		if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create instance!");
		}

		return instance;
	}
}