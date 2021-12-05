#pragma once

#include <vector>

namespace vulkan_kernal
{
	class window_interface
	{
	public:
		virtual ~window_interface() = default;

		virtual std::vector<const char*> get_extensions() const = 0;
		virtual std::pair<int, int> get_framebuffer_size() const = 0;
		virtual bool has_size_changed() const = 0;
		virtual bool initialize(const int width, const int height, const char* title) = 0;
		virtual void poll_events() const = 0;
		virtual void set_resized() = 0;
		virtual bool should_close() const = 0;
	};
}