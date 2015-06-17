/*****************************************************************
 * Transform.cpp
 *****************************************************************
 * Created on: 17.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "Transform.h"

namespace fuel
{
	Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
		:m_position(position), m_rotation(rotation), m_scale(scale){ }

	Transform::Transform(const glm::vec3 &position)
		:m_position(position), m_rotation({0,0,0}), m_scale({1,1,1}){ }

	Transform::Transform(void)
		:m_position({0,0,0}), m_rotation({0,0,0}), m_scale({1,1,1}){ }

	glm::mat4 Transform::calculateWorldMatrix(void)
	{
		static const float PI = 3.14159265359f;
		glm::mat4 translate = glm::translate(glm::mat4(), m_position);
		glm::mat4 pitch = glm::rotate(glm::mat4(), m_rotation.x / 180.f * PI, {1,0,0});
		glm::mat4 yaw = glm::rotate(glm::mat4(), m_rotation.y / 180.f * PI, {0,1,0});
		glm::mat4 roll = glm::rotate(glm::mat4(), m_rotation.z / 180.f * PI, {0,0,1});
		glm::mat4 scale = glm::scale(glm::mat4(), m_scale);

		return translate * pitch * yaw * roll * scale;
	}
}
