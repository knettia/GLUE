#pragma once

namespace glue
{
	class textured_interface : public interface
	{
	public:
		textured_interface() = default;

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