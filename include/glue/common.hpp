#pragma once

#include <vector>

void glue_process(std::vector<glue::interface *> interface_objects, const unsigned int screen_width, const unsigned int screen_height)
{
	for (glue::interface *intf: interface_objects)
	{
		if (nullptr == intf->get_parent())
		{
			intf->calculate_screen_metrics(glue::data_vec2(0, 0), screen_width, screen_height);
		}
	}
}
