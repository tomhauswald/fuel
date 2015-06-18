/*
 * PointLight.h
 *
 *  Created on: 18.06.2015
 *      Author: HAUSWALD, Tom
 */

#ifndef GRAPHICS_LIGHTING_POINTLIGHT_H_
#define GRAPHICS_LIGHTING_POINTLIGHT_H_

#include "Light.h"

namespace fuel
{
	/**
	 * Point light.
	 */
	struct PointLight : public Light
	{
	private:
		// Threshold value to determine light radius.
		// Any pixel that would receive less light than this
		// threshold is considered unlit.
		static constexpr float THRESHOLD = 1.0f / 256.0f;

	public:
		// Linear attenuation factor
		float linearAttenuation;

		// Quadratic attenuation factor
		float quadraticAttenuation;

		/**
		 * Calculates the intensity of the light at the given distance from its position.
		 *
		 * @param distance
		 * 		Distance from light source.
		 */
		inline float getIntensity(float distance) const
		{
			float intensity = 1 / (1 + linearAttenuation * distance + quadraticAttenuation * std::pow(distance, 2));
			return CLAMP(intensity, 0.0f, 1.0f);
		}

		/**
		 * Calculates this point light source's radius.
		 */
		inline float getRadius(void) const
		{
			float lasqr = std::pow(linearAttenuation, 2); 	 // linear attenuation squared
			float qasqr = std::pow(quadraticAttenuation, 2); // quadratic attenuation squared
			float radius = quadraticAttenuation;
			radius *= std::sqrt(
				(lasqr * THRESHOLD
				- 4 * quadraticAttenuation * THRESHOLD
				+ 4 * quadraticAttenuation
				) / (qasqr * THRESHOLD)
			);
			radius /= 2 * quadraticAttenuation;
			return radius;
		}

		inline void setRadius(float linear, float radius)
		{

		}
	};
}

#endif /* GRAPHICS_LIGHTING_POINTLIGHT_H_ */
