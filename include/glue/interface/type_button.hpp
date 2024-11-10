#pragma once

// std
#include <functional>

namespace glue
{
	class button_interface : public interface
	{
	private:
		bool pressed = false;

		std::function<void()> pressed_function;
		std::function<void()> unpressed_function;
	public:
		button_interface() = default;

		bool is_in_bounds(const int x, const int y) const
		{
			return
			(
				x >= screen_position.x && x < screen_position.x + screen_size.x &&
                		y >= screen_position.y && y < screen_position.y + screen_size.y
			);
		}

		bool is_pressed() const
		{
			return pressed;
		}

		void set_pressed_function(std::function<void()> func)
		{
			pressed_function = func;
		}

		void press()
		{
			if (!pressed)
			{
				pressed = true;
				if (pressed_function)
				{
					pressed_function();
				}
			}
		}

		void set_unpressed_function(std::function<void()> func)
		{
			unpressed_function = func;
		}

		void unpress()
		{
			if (pressed)
			{
				pressed = false;
				if (unpressed_function) 
				{
					unpressed_function();
				}
			}
		}
	};
}