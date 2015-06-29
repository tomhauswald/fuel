/*****************************************************************
 * GLUniform.cpp
 *****************************************************************
 * Created on: 14.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "GLUniform.h"
#include <glm/gtc/type_ptr.hpp>

namespace fuel
{
	GLUniform::GLUniform(GLuint programID, const string &name)
		:m_parentProgramID(programID), m_name(name)
	{
		m_location = glGetUniformLocation(programID, name.c_str());
	}

	// Get as float
	template<>
	float GLUniform::get<float>(void)
	{
		ensureParentUsage();
		GLfloat value;
		glGetUniformfv(m_parentProgramID, m_location, &value);
		return value;
	}

	// Set as float
	template<>
	void GLUniform::set<float>(const float &value)
	{
		ensureParentUsage();
		glUniform1f(m_location, value);
	}

	// Get as signed integer (e.g. texture unit)
	template<>
	GLint GLUniform::get<GLint>(void)
	{
		ensureParentUsage();
		GLint value;
		glGetUniformiv(m_parentProgramID, m_location, &value);
		return value;
	}

	// Set as signed integer (e.g. texture unit)
	template<>
	void GLUniform::set<GLint>(const GLint &value)
	{
		ensureParentUsage();
		glUniform1i(m_location, value);
	}

	// Get as 3D vector
	template<>
	glm::vec3 GLUniform::get<glm::vec3>(void)
	{
		ensureParentUsage();
		GLfloat values[3];
		glGetUniformfv(m_parentProgramID, m_location, values);
		return glm::make_vec3(values);
	}

	// Set as 3D vector
	template<>
	void GLUniform::set<glm::vec3>(const glm::vec3 &value)
	{
		ensureParentUsage();
		glUniform3fv(m_location, 1, glm::value_ptr(value));
	}

	// Get as 4x4 matrix
	template<>
	glm::mat4x4 GLUniform::get<glm::mat4x4>(void)
	{
		ensureParentUsage();
		GLfloat values[16];
		glGetUniformfv(m_parentProgramID, m_location, values);
		return glm::make_mat4x4(values);
	}

	// Set as 4x4 matrix
	template<>
	void GLUniform::set<glm::mat4x4>(const glm::mat4x4 &value)
	{
		ensureParentUsage();
		glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(value));
	}
}
