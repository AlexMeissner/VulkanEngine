#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <map>

#include "window_interface.h"

namespace vulkan_kernal
{
	class window_glfw : public window_interface
	{
	public:
		~window_glfw() override;

		VkSurfaceKHR create_surface(const VkInstance instance) const override;

		std::vector<const char*> get_extensions() const override;
		VkExtent2D get_framebuffer_size() const override;
		bool has_size_changed() const override;
		bool initialize(const int width, const int height, const char* title) override;
		void poll_events() const override;
		void set_resized() override;
		bool should_close() const override;

	private:
		static std::map<GLFWwindow*, bool> resized_map;
		static void resize_callback(GLFWwindow* window, int width, int height);

	private:
		GLFWwindow* window = nullptr;
	};
}