/*
 * Light.h
 *
 *  Created on: 18.06.2015
 *      Author: HAUSWALD, Tom
 */

#ifndef GRAPHICS_LIGHTING_LIGHT_H_
#define GRAPHICS_LIGHTING_LIGHT_H_

#include "../../core/Transform.h"

namespace fuel
{
	/**
	 * Represents a 3-dimensional base light object.
	 */
	struct Light
	{
		// Light position
		glm::vec3 position;

		// Light color
		glm::vec3 color;
	};
}

#endif /* GRAPHICS_LIGHTING_LIGHT_H_ */
