#pragma once

namespace glue
{
	class world_interface : public interface
	{
	private:
		vec2 origin_position;
	public:
		world_interface()
			: interface(),
			origin_position(0.0f, 0.0f),
			world_position(0.0f, 0.0f, 0.0f) {}

		interface_type get_type() const override
		{
			return interface_type::_WORLD_INTERFACE;
		}

		vec3 world_position;

		void calculate_screen_frame(const vec3 camera_position, const vec3 camera_up, const vec3 camera_right, const float camera_fov, const int reference_width, const int reference_height)
		{
			mat4 view_matrix = create_view_matrix(camera_position, world_position, camera_up);

			float aspect_ratio = reference_width, reference_height;
		}

		void calculate_screen_metrics(const int reference_width, const int reference_height) override
		{
			vec2 reference = vec2(reference_width, reference_height);

			vec2 calculated_position = reference * position.norm;
			vec2 calculated_size = reference * size.norm;

			calculated_position = vec2(std::ceil(calculated_position.x), std::ceil(calculated_position.y));
			calculated_size = vec2(std::ceil(calculated_size.x), std::ceil(calculated_size.y));

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

			vec2 pivot_offset = (calculated_size * pivot.norm) + (size.abs * pivot.norm) + pivot.abs;

			screen_position = origin_position + calculated_position - pivot_offset + position.abs;
			screen_size = calculated_size + size.abs;

			for (auto *intf : children)
				intf->calculate_screen_metrics( this->screen_size.x, this->screen_size.y);
		}
	};
}