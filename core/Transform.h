/*****************************************************************
 * Transform.h
 *****************************************************************
 * Created on: 17.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef CORE_TRANSFORM_H_
#define CORE_TRANSFORM_H_

#include "Util.h"
#include "../graphics/GLCalls.h"

namespace fuel
{
	class Transform
	{
	private:
		// Position
		glm::vec3 m_position;

		// Rotation around each axis
		glm::vec3 m_rotation;

		// Scale factors
		glm::vec3 m_scale;

	public:
		/**
		 * Instantiates a new transform.
		 */
		Transform(void);

		/**
		 * Instantiates a new transform.
		 *
		 * @param position
		 * 		Position.
		 */
		Transform(const glm::vec3 &position);

		/**
		 * Instantiates a new transform.
		 *
		 * @param position
		 * 		Position.
		 *
		 * @param rotation
		 * 		Rotation.
		 *
		 * @param scale
		 * 		Scale.
		 */
		Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

		/**
		 * Returns the transform's position.
		 *
		 * @return Position.
		 */
		inline glm::vec3 &getPosition(void) { return m_position; }

		/**
		 * Returns the transform's position.
		 *
		 * @return Position.
		 */
		inline const glm::vec3 &getPosition(void) const{ return m_position; }

		/**
		 * Sets the transform's position.
		 *
		 * @param position
		 * 		The new position.
		 */
		inline void setPosition(const glm::vec3 &position){ m_position = position; }

		/**
		 * Returns the transform's rotation.
		 *
		 * @return Rotation.
		 */
		inline glm::vec3 &getRotation(void) { return m_rotation; }

		/**
		 * Returns the transform's rotation.
		 *
		 * @return Rotation.
		 */
		inline const glm::vec3 &getRotation(void) const{ return m_rotation; }

		/**
		 * Sets the transform's rotation.
		 *
		 * @param rotation
		 * 		The new rotation.
		 */
		inline void setRotation(const glm::vec3 &rotation){ m_rotation = rotation; }

		/**
		 * Returns the transform's scale.
		 *
		 * @return Scale.
		 */
		inline glm::vec3 &getScale(void) { return m_scale; }

		/**
		 * Returns the transform's scale.
		 *
		 * @return Scale.
		 */
		inline const glm::vec3 &getScale(void) const{ return m_scale; }

		/**
		 * Sets the transform's scale.
		 *
		 * @param scale
		 * 		The new scale.
		 */
		inline void setScale(const glm::vec3 &scale){ m_scale = scale; }

		/**
		 * Calculates and returns the world matrix according to this
		 * transform's orientation.
		 *
		 * @return World (a.k.a. model-) matrix.
		 */
		glm::mat4 calculateWorldMatrix(void);
	};
}

#endif // CORE_TRANSFORM_H_
