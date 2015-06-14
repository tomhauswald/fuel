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
	namespace graphics
	{
		namespace shaders
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
				GLfloat value;
				glGetUniformfv(m_parentProgramID, m_location, &value);
				return value;
			}

			// Set as float
			template<>
			void GLUniform::set<float>(const float &value)
			{
				glUniform1f(m_location, value);
			}

			// Get as unsigned integer
			template<>
			uint32_t GLUniform::get<uint32_t>(void)
			{
				GLuint value;
				glGetUniformuiv(m_parentProgramID, m_location, &value);
				return value;
			}

			// Set as unsigned integer
			template<>
			void GLUniform::set<uint32_t>(const uint32_t &value)
			{
				glUniform1ui(m_location, value);
			}

			// Get as 4x4 matrix
			template<>
			glm::mat4x4 GLUniform::get<glm::mat4x4>(void)
			{
				GLfloat values[16];
				glGetUniformfv(m_parentProgramID, m_location, values);
				return glm::make_mat4x4(values);
			}

			// Set as 4x4 matrix
			template<>
			void GLUniform::set<glm::mat4x4>(const glm::mat4x4 &value)
			{
				glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(value));
			}
		}
	}
}
