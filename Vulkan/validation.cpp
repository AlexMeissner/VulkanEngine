#include "validation.h"
#include "vulkan_settings.h"

//#define NOMINMAX
#include <Windows.h>
#include <iostream>

namespace vulkan_kernal::validation_layers
{
	VKAPI_ATTR VkBool32 VKAPI_CALL debug_message_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
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

	VkDebugUtilsMessengerCreateInfoEXT generate_create_info()
	{
		VkDebugUtilsMessengerCreateInfoEXT create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		create_info.pNext = nullptr;
		create_info.flags = message_flags;
		create_info.messageSeverity = message_severity;
		create_info.messageType = message_type;
		create_info.pfnUserCallback = debug_message_callback;
		create_info.pUserData = nullptr;
		return create_info;
	}

	VkDebugUtilsMessengerEXT create(VkInstance instance)
	{
		VkDebugUtilsMessengerEXT messenger = nullptr;

		if (const auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"))
		{
			VkDebugUtilsMessengerCreateInfoEXT create_info = generate_create_info();
			if (func(instance, &create_info, nullptr, &messenger) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create validation layers!");
			}
		}

		return messenger;
	}

	void cleanup(VkInstance instance, VkDebugUtilsMessengerEXT messenger)
	{
		if (const auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"))
		{
			func(instance, messenger, nullptr);
		}
	}

	bool available()
	{
		uint32_t count = 0;
		vkEnumerateInstanceLayerProperties(&count, nullptr);

		std::vector<VkLayerProperties> available_layers(count);
		vkEnumerateInstanceLayerProperties(&count, available_layers.data());

		for (const char* layer_name : names)
		{
			bool found = false;

			for (const auto& properties : available_layers)
			{
				if (strcmp(layer_name, properties.layerName) == 0)
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

		return true;
	}
}