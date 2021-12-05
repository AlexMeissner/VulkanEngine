#include "window_glfw.h"

namespace vulkan_kernal
{
	std::map<GLFWwindow*, bool> window_glfw::resized_map {};

	window_glfw::~window_glfw()
	{
		resized_map.erase(resized_map.find(window));
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	VkSurfaceKHR window_glfw::create_surface(const VkInstance instance) const
	{
		VkSurfaceKHR surface = nullptr;
		glfwCreateWindowSurface(instance, window, nullptr, &surface);
		return surface;
	}

	std::vector<const char*> window_glfw::get_extensions() const
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		return { glfwExtensions, glfwExtensions + glfwExtensionCount };
	}

	std::pair<int, int> window_glfw::get_framebuffer_size() const
	{
		int width = 0, height = 0;
		glfwGetFramebufferSize(window, &width, &height);

		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(window, &width, &height);
			glfwWaitEvents();
		}

		return { width, height };
	}

	bool window_glfw::has_size_changed() const
	{
		return resized_map.at(window);
	}

	bool window_glfw::initialize(const int width, const int height, const char* title)
	{
		if (glfwInit() == GLFW_FALSE)
		{
			return false;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		if (window = glfwCreateWindow(width, height, title, nullptr, nullptr))
		{
			resized_map.emplace(window, false);
			glfwSetWindowUserPointer(window, this);
			glfwSetFramebufferSizeCallback(window, resize_callback);
			return true;
		}

		return false;
	}

	void window_glfw::poll_events() const
	{
		glfwPollEvents();
	}

	void window_glfw::set_resized()
	{
		resized_map[window] = false;
	}

	bool window_glfw::should_close() const
	{
		return glfwWindowShouldClose(window);
	}

	void window_glfw::resize_callback(GLFWwindow* window, int width, int height)
	{
		resized_map[window] = true;
	}
}