#pragma once

#include <vector>
#include <vulkan/vulkan.h>

class validation_layers
{
public:
#ifdef _DEBUG
    ~validation_layers();
#endif

    std::vector<const char*> get_layers() const;
    bool initialize(const VkInstance vk_instance);
    constexpr bool is_enabled() const;

private:
    static VKAPI_ATTR VkBool32 VKAPI_CALL callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT type,
        const VkDebugUtilsMessengerCallbackDataEXT* data,
        void* user_data);

private:
    VkInstance instance = nullptr;
    VkDebugUtilsMessengerEXT messenger = nullptr;
};