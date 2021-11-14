#include "vulkan_instance.h"
#include "logger.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace
{
    VKAPI_ATTR VkBool32 VKAPI_CALL callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* data, void* user_data)
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
}

vulkan_instance::~vulkan_instance()
{
    vkDestroyInstance(instance, nullptr);
}

bool vulkan_instance::initialize()
{
    //if (!validation_layer.initialize(instance))
    //{
    //    return false;
    //}

    VkApplicationInfo application_info{};
    application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    application_info.pApplicationName = "VulkanApp";
    application_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    application_info.pEngineName = "No Engine";
    application_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    application_info.apiVersion = VK_API_VERSION_1_0;
    application_info.pNext = nullptr;

    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    VkInstanceCreateInfo instance_create_info{};
    instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_create_info.pApplicationInfo = &application_info;

    //instance_create_info.enabledLayerCount = static_cast<uint32_t>(validation_layer.get_layers().size());
    //instance_create_info.ppEnabledLayerNames = validation_layer.get_layers().data();

    instance_create_info.ppEnabledExtensionNames = glfw_extensions; // TODO: Concat
    instance_create_info.enabledExtensionCount = glfw_extension_count; // TODO: Concat

    if (vkCreateInstance(&instance_create_info, nullptr, &instance) != VK_SUCCESS)
    {
        logger::error("vulkan instance creation failed");
        return false;
    }

    return true;
}