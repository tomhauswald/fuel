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

			return quadraticAttenuation * std::sqrt(
				(lasqr * THRESHOLD
				- 4 * quadraticAttenuation * THRESHOLD
				+ 4 * quadraticAttenuation
				) / (qasqr * THRESHOLD)
			) / (2 * quadraticAttenuation);
		}

		/**
		 * Sets the light attenuation factors using a given linear attenuation
		 * and desired radius.
		 *
		 * @param linear
		 * 		Linear attenuation factor.
		 *
		 * 	@param radius
		 * 		Desired light radius.
		 */
		inline void setRadius(float linear, float radius)
		{
			// Radius squared
			float rsqr = std::pow(radius, 2);

			// Reordering equation to 0 = X^2 + PX + Q results in:
			float p = 1.0f / rsqr - 1.0f / (THRESHOLD * rsqr);
			float q = - std::pow(linear, 2) / (4 * rsqr);
			quadraticAttenuation = SOLVEQUADRATIC(p, q);
		}
	};
}

#endif /* GRAPHICS_LIGHTING_POINTLIGHT_H_ */
