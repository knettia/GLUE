#pragma once

namespace glue
{
	class textured_interface : public interface
	{
	private:
		unsigned int texture;
	public:
		textured_interface()
			: interface(),
			image_opacity(0.0f),
			image_hue(1.0f, 1.0f, 1.0f) {}

		interface_type get_type() const override
		{
			return interface_type::_TEXTURED_INTERFACE;
		}

		unsigned_float image_opacity;
		vec3 image_hue;

		unsigned int get_texture()
		{
			return texture;
		}

		void set_texture(unsigned int t)
		{
			texture = t;
		}

		[[nodiscard]] std::vector<float> get_vertices(int reference_width, int reference_height) const override
		{
			float calculated_screen_x = (screen_position.x / reference_width) * 2.0f - 1.0f;
			float calculated_screen_y = 1.0f - (screen_position.y / reference_height) * 2.0f;

			float calculated_screen_width = (screen_size.x / reference_width) * 2.0f;
			float calculated_screen_height = (screen_size.y / reference_height) * 2.0f;

			return
			{
			//      position                                                                                       texture
				calculated_screen_x, calculated_screen_y - calculated_screen_height,                           0.0f, 0.0f,
				calculated_screen_x + calculated_screen_width, calculated_screen_y - calculated_screen_height, 1.0f, 0.0f,
				calculated_screen_x + calculated_screen_width, calculated_screen_y,                            1.0f, 1.0f,
				calculated_screen_x, calculated_screen_y,                                                      0.0f, 1.0f
			};
		}
	};
}