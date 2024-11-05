#pragma once

#include <vector>

namespace glue {
	void process(std::vector<interface *> interface_objects, const unsigned int screen_width, const unsigned int screen_height)
	{
		for (interface *intf: interface_objects)
		{
			if (nullptr == intf->get_parent())
			{
				intf->calculate_screen_metrics(data_vec2(0, 0), screen_width, screen_height);
			}
		}
	}
}
