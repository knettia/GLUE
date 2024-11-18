#pragma once

// std
#include <vector>

namespace glue {
	void process(std::vector<interface *> &interface_objects, const unsigned int screen_width, const unsigned int screen_height)
	{
		std::sort(interface_objects.begin(), interface_objects.end(), 
		[](const glue::interface *a, const glue::interface *b)
		{
			return a->z_layer < b->z_layer;
		});


		for (interface *intf: interface_objects)
		{
			if (nullptr == intf->get_parent())
			{
				intf->calculate_screen_metrics(screen_width, screen_height);
			}
		}
	}
}
