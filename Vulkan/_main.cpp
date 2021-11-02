#include <Windows.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class vulkan_application
{
public:
    void run()
    {
        if (initialize_window(800, 600))
        {
            initialize();
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

    void initialize()
    {

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
};

int main()
{
    vulkan_application app;
    app.run();

    return EXIT_SUCCESS;
}