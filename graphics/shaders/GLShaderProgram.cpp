/*****************************************************************
 * GLShaderProgram.cpp
 *****************************************************************
 * Created on: 14.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "GLShaderProgram.h"

namespace fuel
{
	GLShaderProgram::GLShaderProgram(void)
		:m_ID(GL_NONE)
	{
		m_ID = glCreateProgram();

		if(m_ID == GL_NONE)
		{
			cerr << "Could not generate OpenGL shader program." << endl;
		}
		else
		{
			cout << "Generated OpenGL shader program: " << m_ID << endl;
			this->use();
		}
	}

	void GLShaderProgram::setShader(EGLShaderType type, const string &filename)
	{
		// Already contains shader of this type
		if(m_shaders.count(type) > 0)
		{
			// Detach old shader
			detachShader(m_shaders[type]);
			m_shaders.erase(type);
		}

		// Store and attach new shader
		m_shaders[type] = make_unique<GLShader>(type, filename);
		attachShader(m_shaders[type]);
	}

	GLShaderProgram::~GLShaderProgram(void)
	{
		for(const auto &shader : m_shaders)
		{
			detachShader(shader.second);
		}

		m_shaders.clear();
		m_uniforms.clear();

		if(m_ID != GL_NONE)
		{
			cout << "Deleting OpenGL shader program: " << m_ID << endl;
			glDeleteProgram(m_ID);
			m_ID = GL_NONE;
		}
	}
}


