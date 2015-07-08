/*****************************************************************
 * GLShader.cpp
 *****************************************************************
 * Created on: 14.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <fstream>
#include "GLShader.h"
#include "../../core/Util.h"

namespace fuel
{
	GLShader::GLShader(EGLShaderType type, const string &filename)
		:m_ID(GL_NONE), m_type(type)
	{
		// Check if file exists
		if(!fileExists(filename))
		{
			cerr << "Shader source file '" << filename << "' does not exist." << endl;
		}

		// File exists
		else
		{
			// Create shader
			m_ID = glCreateShader(getShaderTypeConstant(type));

			if(m_ID == GL_NONE)
			{
				cerr << "Could not create OpenGL shader." << endl;
			}

			// Successfully created shader
			else
			{
				cout << "Created OpenGL shader: " << m_ID << endl;

				// Load shader source
				string line, source;
				ifstream sourceStream(filename);
				while(sourceStream.good() && !sourceStream.eof())
				{
					getline(sourceStream, line);
					source.append(line + "\n");
				}

				// Compile shader
				const char *sourceCString = source.c_str();
				glShaderSource(m_ID, 1, &sourceCString, nullptr);
				glCompileShader(m_ID);

				// Check compilation
				GLint compileResult;
				glGetShaderiv(m_ID, GL_COMPILE_STATUS, &compileResult);
				if(compileResult != GL_TRUE)
				{
					cerr << "Shader compilation of file '" << filename << "' failed." << endl;

					GLsizei logLength;
					GLchar  log[1024];
					glGetShaderInfoLog(	m_ID, sizeof(log), &logLength, log);

					cerr << "Shader info log: " << endl << log << endl;
				}

				// Compilation worked
				else
				{
					cout << "Successfully compiled shader '" << filename << "'" << endl;
				}
			}
		}
	}

	GLenum GLShader::getShaderTypeConstant(EGLShaderType type)
	{
		switch( type )
		{
			case EGLShaderType::COMPUTE:
				return GL_COMPUTE_SHADER;

			case EGLShaderType::VERTEX:
				return GL_VERTEX_SHADER;

			case EGLShaderType::TESS_CTRL:
				return GL_TESS_CONTROL_SHADER;

			case EGLShaderType::TESS_EVAL:
				return GL_TESS_EVALUATION_SHADER;

			case EGLShaderType::GEOMETRY:
				return GL_GEOMETRY_SHADER;

			case EGLShaderType::FRAGMENT:
				return GL_FRAGMENT_SHADER;

			default:
				return GL_VERTEX_SHADER;
		}
	}

	GLShader::~GLShader(void)
	{
		if(m_ID != GL_NONE)
		{
			cout << "Deleting OpenGL shader: " << m_ID << endl;
			glDeleteShader(m_ID);
			m_ID = GL_NONE;
		}
	}
}
