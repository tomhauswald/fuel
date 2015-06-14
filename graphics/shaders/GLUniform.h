/*****************************************************************
 * GLUniform.h
 *****************************************************************
 * Created on: 14.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_SHADERS_GLUNIFORM_H_
#define GRAPHICS_SHADERS_GLUNIFORM_H_

#include "../GLWindow.h"
#include <cassert>

namespace fuel
{
	namespace graphics
	{
		namespace shaders
		{
			class GLUniform
			{
			private:
				// OpenGL shader program ID of parent
				GLuint m_parentProgramID;

				// Uniform location
				GLint m_location;

				// Uniform name
				string m_name;

			public:
				/**
				 * Instantiates a new GLSL uniform variable.
				 *
				 * @param programID
				 *        Parent shader program ID.
				 * @param name
				 *        Name of the variable.
				 */
				GLUniform(GLuint programID, const string &name);

				/**
				 * Returns the uniform's name.
				 *
				 * @return Name.
				 */
				inline const string &getName(void) const { return m_name; }

				/**
				 * Returns the shader uniform value as the specified type.
				 *
				 * @return Uniform value.
				 */
				template<typename T>
				T get(void);

				/**
				 * Sets the shader uniform value.
				 */
				template<typename T>
				void set(const T &value);
			};
		}
	}
}



#endif // GRAPHICS_SHADERS_GLUNIFORM_H_
