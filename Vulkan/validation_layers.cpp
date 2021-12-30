#include "validation_layers.h"

#define NOMINMAX
#include <Windows.h>
#include <iostream>

namespace vulkan_kernal
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL debug_message_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		switch (messageSeverity)
		{
		case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
			break;

		case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			break;

		case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			break;

		case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			break;
		}

		switch (messageType)
		{
		case VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 206);
			break;

		case VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 236);
			break;
		}

		std::cout << pCallbackData->pMessage << "\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);

		return VK_FALSE;
	}

	validation_layers::validation_layers(const bool enabled)
		: enabled(enabled)
	{
		if (enabled)
		{
			layers = { "VK_LAYER_KHRONOS_validation" };

			create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			create_info.messageSeverity = /*VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |*/ VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			create_info.pfnUserCallback = debug_message_callback;
		}
	}

	bool validation_layers::available() const
	{
		if (enabled)
		{
			uint32_t count;
			vkEnumerateInstanceLayerProperties(&count, nullptr);

			std::vector<VkLayerProperties> available_layers(count);
			vkEnumerateInstanceLayerProperties(&count, available_layers.data());

			for (const char* layerName : layers)
			{
				bool found = false;

				for (const auto& layerProperties : available_layers)
				{
					if (strcmp(layerName, layerProperties.layerName) == 0)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					return false;
				}
			}
		}

		return true;
	}

	void validation_layers::cleanup(const VkInstance instance) const
	{
		if (enabled)
		{
			if (const auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"))
			{
				func(instance, debug_messenger, nullptr);
			}
		}
	}

	uint32_t validation_layers::get_count() const
	{
		return static_cast<uint32_t>(layers.size());
	}

	void* validation_layers::get_create_info() const
	{
		if (enabled)
		{
			return (VkDebugUtilsMessengerCreateInfoEXT*)&create_info;
		}

		return nullptr;
	}

	const char* const* validation_layers::get_names() const
	{
		return layers.data();
	}

	bool validation_layers::initialize(const VkInstance instance)
	{
		if (enabled)
		{
			this->instance = instance;

			if (const auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"))
			{
				return func(instance, &create_info, nullptr, &debug_messenger) == VK_SUCCESS;
			}

			return false;
		}

		return true;
	}
}