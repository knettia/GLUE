#pragma once

// std
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

// GLUE
#include "../vec2.hpp"
#include "../udmi2.hpp"
#include "../unsigned_float.hpp"

constexpr int huge = std::numeric_limits<int>::max();

namespace glue
{
	class interface
	{
	protected:
		data_vec2 screen_position;
		data_vec2 screen_size;

		interface *parent = nullptr;
		std::vector<interface *> children;
	public:
		enum interface_type
		{
			_INTERFACE,
			_BUTTON_INTERFACE,
		};

		interface(udmi2 position = udmi2(), udmi2 size = udmi2(), udmi2 pivot = udmi2()) : position(position), size(size), pivot(pivot) {}
		virtual ~interface() {}

		udmi2 position;
		udmi2 size;
		udmi2 pivot;
		data_vec2 min_size = data_vec2(0, 0);
		data_vec2 max_size = data_vec2(huge, huge);
		unsigned_float aspect_ratio;

		interface_type get_type() const
		{
			return interface_type::_INTERFACE;
		}

		data_vec2 get_screen_position() const
		{
			return screen_position;
		}

		data_vec2 get_screen_size() const
		{
			return screen_size;
		}

		void calculate_screen_metrics(const data_vec2 &origin_position, const int reference_width, const int reference_height)
		{
			data_vec2 reference = data_vec2(reference_width, reference_height);

			data_vec2 calculated_position = reference * position.norm;
			data_vec2 calculated_size = reference * size.norm;

			calculated_position = data_vec2(std::ceil(calculated_position.x), std::ceil(calculated_position.y));
			calculated_size = data_vec2(std::ceil(calculated_size.x), std::ceil(calculated_size.y));

			calculated_size.x = std::clamp(calculated_size.x, min_size.x, max_size.x);
			calculated_size.y = std::clamp(calculated_size.y, min_size.y, max_size.y);

			if (aspect_ratio > 0.0f)
			{
				float current_aspect_ratio = calculated_size.x / calculated_size.y;

				if (current_aspect_ratio > aspect_ratio)
					calculated_size.x = calculated_size.y * aspect_ratio;
				else if (current_aspect_ratio < aspect_ratio)
					calculated_size.y = calculated_size.x / aspect_ratio;
			}

			data_vec2 pivot_offset = (calculated_size * pivot.norm) + (size.abs * pivot.norm) + pivot.abs;

			screen_position = origin_position + calculated_position - pivot_offset + position.abs;
			screen_size = calculated_size + size.abs;

			for (auto *intf : children)
				intf->calculate_screen_metrics(this->screen_position, this->screen_size.x, this->screen_size.y);
		}

		[[nodiscard]] virtual std::vector<float> get_vertices(int reference_width, int reference_height) const
		{
			float calculated_screen_x = (screen_position.x / reference_width) * 2.0f - 1.0f;
			float calculated_screen_y = 1.0f - (screen_position.y / reference_height) * 2.0f;

			float calculated_screen_width = (screen_size.x / reference_width) * 2.0f;
			float calculated_screen_height = (screen_size.y / reference_height) * 2.0f;

			return
			{
				calculated_screen_x, calculated_screen_y - calculated_screen_height,
				calculated_screen_x + calculated_screen_width, calculated_screen_y - calculated_screen_height,
				calculated_screen_x + calculated_screen_width, calculated_screen_y,
				calculated_screen_x, calculated_screen_y
			};
		}

		std::vector<interface *> get_children() const
		{
			return children;
		}

		template <typename intfT>
		std::vector<intfT *> get_children_of_type() const
		{
			static_assert(std::is_base_of<interface, intfT>::value, "only types derived from interface can be returned.");
			std::vector<intfT *> result;
			for (auto *intf : children)
			{
				if (intfT *derived = dynamic_cast<intfT *>(intf))
				{
					result.push_back(derived);
				}
			}
			return result;
		}

		void remove_child(interface &intf)
		{
			children.erase(std::remove(children.begin(), children.end(), &intf), children.end());
			intf.parent = nullptr;
		}

		void set_child(interface &intf)
		{
			if (intf.parent != nullptr) {
				intf.parent->remove_child(intf);
			}

			intf.parent = this;
			children.push_back(&intf);
		}

		interface *get_parent()
		{
			return parent;
		}

		void set_parent(interface &intf)
		{
			if (parent != nullptr)
			{
				parent->remove_child(*this);
			}

			parent = &intf;
			intf.set_child(*this);
		}
	};
}