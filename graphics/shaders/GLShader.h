/*****************************************************************
 * GLShader.h
 *****************************************************************
 * Created on: 14.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_SHADERS_GLSHADER_H_
#define GRAPHICS_SHADERS_GLSHADER_H_

#include "../GLWindow.h"

namespace fuel
{
	namespace graphics
	{
		namespace shaders
		{
			/**
			 * OpenGL shader types.
			 */
			enum class EGLShaderType : uint8_t
			{
				COMPUTE,  //!< COMPUTE
				VERTEX,   //!< VERTEX
				TESS_CTRL,//!< TESS_CTRL
				TESS_EVAL,//!< TESS_EVAL
				GEOMETRY, //!< GEOMETRY
				FRAGMENT  //!< FRAGMENT
			};

			/**
			 * OpenGL shader wrapper class.
			 */
			class GLShader
			{
			private:
				// OpenGL shader ID
				GLuint m_ID;

				// Shader type
				EGLShaderType m_type;

			public:
				/**
				 * Instantiates a new shader and loads it's sourcecode from the given location.
				 *
				 * @param type
				 * 		Shader type.
				 *
				 * @param filename
				 * 		Shader source file.
				 */
				GLShader(EGLShaderType type, const string &filename);

				/**
				 * Returns the OpenGL shader ID.
				 *
				 * @return ID.
				 */
				inline GLuint getID(void) const { return m_ID; }

				/**
				 * Returns the shader type.
				 *
				 * @return Shader type.
				 */
				inline EGLShaderType getType(void) const { return m_type; }

				/**
				 * Converts an EGLShaderType value to its corresponding OpenGL integral identifier.
				 *
				 * @param type
				 *        The shader type enum value.
				 * @return OpenGL shader type value.
				 */
				static GLenum getShaderTypeConstant(EGLShaderType type);

				/**
				 * Release OpenGL shader.
				 */
				~GLShader(void);
			};
		}
	}
}


#endif // GRAPHICS_SHADERS_GLSHADER_H_
