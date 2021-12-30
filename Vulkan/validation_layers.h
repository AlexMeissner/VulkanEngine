#pragma once

#include <vulkan/vulkan.h>
#include <stdint.h>
#include <vector>

namespace vulkan_kernal
{
	class validation_layers
	{
	public:
		validation_layers() = delete;
		validation_layers(const bool enabled);

		bool available() const;
		void cleanup(const VkInstance instance) const;
		uint32_t get_count() const;
		void* get_create_info() const;
		const char* const* get_names() const;
		bool initialize(const VkInstance instance);

	private:
		const bool enabled = false;
		std::vector<const char*> layers;
		VkInstance instance = nullptr;
		VkDebugUtilsMessengerEXT debug_messenger = nullptr;
		VkDebugUtilsMessengerCreateInfoEXT create_info{};
	};
}