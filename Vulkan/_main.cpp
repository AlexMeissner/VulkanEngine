#include <Windows.h>

#include "logger.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class vulkan_application
{
public:
    void run()
    {
        if (initialize_window(800, 600) &&
            initialize_vulkan())
        {
            loop();
            cleanup();
        }
    }

private:
    bool initialize_window(const uint32_t width, const uint32_t height)
    {
        if (glfwInit() != GL_TRUE)
        {
            return false;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

        if (!window)
        {
            return false;
        }

        return true;
    }

    bool initialize_vulkan()
    {
        return true;
    }

    void create_instance()
    {
        VkApplicationInfo application_info{};
        application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        application_info.pApplicationName = "VulkanApp";
        application_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        application_info.pEngineName = "No Engine";
        application_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        application_info.apiVersion = VK_API_VERSION_1_0;
    }

    void loop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    GLFWwindow* window = nullptr;
    VkInstance instance = nullptr;
};

int main()
{
    vulkan_application app;
    app.run();

    return EXIT_SUCCESS;
}