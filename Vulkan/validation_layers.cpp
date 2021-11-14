#include "validation_layers.h"
#include "logger.h"
#include <vulkan/vulkan.h>

validation_layers::~validation_layers()
{
    if (const auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"))
    {
        func(instance, messenger, nullptr);
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL validation_layers::callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* data, void* user_data)
{
    switch (severity)
    {
    case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        logger::info(data->pMessage);
        break;

    case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        logger::info(data->pMessage);
        break;

    case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        logger::warning(data->pMessage);
        break;

    case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        logger::critical(data->pMessage);
        break;
    }

    return VK_FALSE;
}

#ifdef _DEBUG
std::vector<const char*> validation_layers::get_layers() const
{
    return
    {
        "VK_LAYER_KHRONOS_validation"
    };
}

bool validation_layers::initialize(const VkInstance vk_instance)
{
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    std::vector<VkLayerProperties> available_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

    for (const char* layer_name : get_layers())
    {
        bool layer_found = false;

        for (const auto& layerProperties : available_layers)
        {
            if (strcmp(layer_name, layerProperties.layerName) == 0)
            {
                layer_found = true;
                break;
            }
        }

        if (!layer_found)
        {
            logger::error(std::string("validation layers not available: ") + layer_name);
            return false;
        }
    }

    if (const auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"))
    {
        instance = vk_instance;

        VkDebugUtilsMessengerCreateInfoEXT create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback = callback;
        create_info.pUserData = nullptr;

        return func(instance, &create_info, nullptr, &messenger) == VK_SUCCESS;
    }
    else
    {
        logger::error("validation layer messanger creation failed");
        return false;
    }
}

constexpr bool validation_layers::is_enabled() const
{
    return true;
}

#else

std::vector<const char*> validation_layers::get_layers() const
{
    return {};
}

bool validation_layers::initialize(const VkInstance)
{
    return true;
}

constexpr bool validation_layers::is_enabled() const
{
    return false;
}
#endif