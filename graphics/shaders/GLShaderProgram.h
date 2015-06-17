/*****************************************************************
 * GLShaderProgram.h
 *****************************************************************
 * Created on: 14.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_SHADERS_GLSHADERPROGRAM_H_
#define GRAPHICS_SHADERS_GLSHADERPROGRAM_H_

#include <map>
#include "../../core/Util.h"
#include "../GLWindow.h"
#include "GLUniform.h"
#include "GLShader.h"

namespace fuel
{
	class GLShaderProgram
	{
	private:
		// OpenGL shader program ID
		GLuint m_ID;

		// Shaders used
		map<EGLShaderType, unique_ptr<GLShader>> m_shaders;

		// Registered uniform variables
		map<string, unique_ptr<GLUniform>> m_uniforms;

		/**
		 * Attaches a shader to this program.
		 *
		 * @param shader
		 *		The shader to attach.
		 */
		inline void attachShader(const unique_ptr<GLShader> &shader){ glAttachShader(m_ID, shader->getID()); }

		/**
		 * Detaches a shader from this program.
		 *
		 * @param shader
		 *		The shader to detach.
		 */
		inline void detachShader(const unique_ptr<GLShader> &shader){ glDetachShader(m_ID, shader->getID()); }

	public:
		/**
		 * Instantiates a new OpenGL shader program.
		 */
		GLShaderProgram(void);

		/**
		 * Returns the program ID.
		 *
		 * @return Program ID.
		 */
		inline GLuint getID(void) const { return m_ID; }

		/**
		 * Registers a new uniform variable.
		 *
		 * @param name
		 *            The uniform's name.
		 */
		inline void registerUniform(const string &name)
		{
			m_uniforms[name] = make_unique<GLUniform>(m_ID, name);
		}

		/**
		 * Returns a uniform variable.
		 *
		 * @param name
		 *            The uniform's name.
		 * @return The uniform variable.
		 */
		inline GLUniform &getUniform(const string &name){ return *m_uniforms[name]; }

		/**
		 * Use this shader program for the following draw calls.
		 */
		inline void use(void){ glUseProgram(m_ID); }

		/**
		 * Sets one of the program's shaders.
		 * Loads the source from the specified file name.
		 * If any shader was attached before, it is released.
		 *
		 * @param type
		 *            Shader type.
		 * @param filename
		 *            Shader source file.
		 */
		void setShader(EGLShaderType type, const string &filename);

		/**
		 * Binds a vertex attribute name to the designated ID.
		 * This attribute can then be used inside shader code.
		 *
		 * @param attributeID
		 *            Attribute ID.
		 * @param name
		 *            The name to use for the attribute.
		 */
		inline void bindVertexAttribute(GLuint attributeID, const string &name)
		{
			glBindAttribLocation(m_ID, attributeID, name.c_str());
		}

		/**
		 * Validates the shader in order to make it usable in the future.
		 * All vertex attributes must be bound beforehand and all uniforms
		 * registered afterwards.
		 */
		inline void link(void){ glLinkProgram(m_ID); glValidateProgram(m_ID); }

		/**
		 * Delete attached shaders and the program itself.
		 */
		~GLShaderProgram(void);
	};
}

#endif // GRAPHICS_SHADERS_GLSHADERPROGRAM_H_
