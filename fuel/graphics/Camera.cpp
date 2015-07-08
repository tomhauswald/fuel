/*****************************************************************
 * Camera.cpp
 *****************************************************************
 * Created on: 18.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "Camera.h"

namespace fuel
{
	Camera::Camera()
	{
		;;
	}

	glm::mat4 Camera::calculateViewMatrix(void) const
	{
		const glm::vec3 &pos = m_transform.getPosition();
		const glm::vec3 &rot = m_transform.getRotation();

		glm::mat4 pitch = glm::rotate(glm::mat4(), rot.x / 180.f * PI, {1,0,0});
		glm::mat4 yaw   = glm::rotate(glm::mat4(), rot.y / 180.f * PI, {0,1,0});
		glm::mat4 roll  = glm::rotate(glm::mat4(), rot.z / 180.f * PI, {0,0,1});
		glm::vec4 offset = (pitch * yaw * roll) * glm::vec4(0, 0, -1, 0);

		return glm::lookAt(pos, pos + glm::vec3(offset), {0, 1, 0});
	}
}
