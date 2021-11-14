#pragma once

#include <vulkan/vulkan.h>

class vulkan_instance
{
public:
    ~vulkan_instance();

    bool initialize();

private:
    VkInstance instance = nullptr;
    VkDebugUtilsMessengerEXT messenger = nullptr;
};