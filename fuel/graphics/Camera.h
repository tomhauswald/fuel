/*****************************************************************
 * Camera.h
 *****************************************************************
 * Created on: 18.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_CAMERA_H_
#define GRAPHICS_CAMERA_H_

#include "../core/Transform.h"

namespace fuel
{
	/**
	 * Represents a simple camera.
	 */
	class Camera
	{
	private:
		// Camera transform
		Transform m_transform;

	public:
		/**
		 * Instantiates a new camera at the world origin.
		 */
		Camera(void);

		/**
		 * Returns the camera transform.
		 *
		 * @return Camera transform.
		 */
		inline Transform &getTransform(void){ return m_transform; }

		/**
		 * Returns the camera transform. [readonly]
		 *
		 * @return Camera transform.
		 */
		inline const Transform &getTransform(void) const { return m_transform; }

		/**
		 * Calculates and returns the view matrix of this camera.
		 *
		 * @return View matrix.
		 */
		glm::mat4 calculateViewMatrix(void) const;
	};
}



#endif // GRAPHICS_CAMERA_H_
