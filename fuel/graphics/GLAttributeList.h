/*****************************************************************
 * GLAttributeList.h
 *****************************************************************
 * Created on: 11.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_GLATTRIBUTELIST_H_
#define GRAPHICS_GLATTRIBUTELIST_H_

#include "GLBuffer.h"
#include <memory>
#include <vector>

namespace fuel
{
	/*****************************************************************
	 * Wrapper class for OpenGL attribute list stored inside a VAO.
	 *****************************************************************/
	class GLAttributeList
	{
	private:
		// Attribute list ID (relative to VAO)
		GLuint m_ID;

		// Underlying array buffer (VBO)
		std::unique_ptr<GLBuffer> m_pArrayBuffer;

	public:
		/**
		 * Instantiates a new OpenGL attribute list.
		 *
		 * @param id
		 *        	Attribute list ID.
		 */
		GLAttributeList(GLuint id);

		/**
		 * Returns the attribute list ID.
		 *
		 * @return ID.
		 */
		inline GLuint getID(void) const { return m_ID; }

		/**
		 * Returns a readonly reference to the underlying array buffer. (VBO)
		 *
		 * @return Underlying buffer.
		 */
		inline const GLBuffer &getBuffer(void) const { return *m_pArrayBuffer; }

		/**
		 * Write data to this attribute list.
		 * This binds the underlying array buffer and unbinds any after completion.
		 * The data type to use has to be specified as template
		 * parameter as well as OpenGL enumeration value.
		 *
		 * Example: To write Vector3f's call (.., 3, GL_FLOAT, {..,floats,..})
		 *
		 * @param usage
		 *        	OpenGL usage enumeration value. (GL_STATIC_DRAW, ..)
		 * @param groupSize
		 *      	The number of objects belonging to each value.
		 * @param datatyoe
		 * 			OpenGL datatype specifier.
		 * @param data
		 *      	The data as readonly vector reference.
		 */
		template<typename DATATYPE, GLuint GROUPSIZE>
		void write(GLenum usage, GLenum datatype, const std::vector<DATATYPE> &data)
		{
			GLBuffer::bind(*m_pArrayBuffer);
			m_pArrayBuffer->write(usage, data);
			glEnableVertexAttribArray(m_ID);
			glVertexAttribPointer(m_ID, GROUPSIZE, datatype, GL_FALSE, 0, nullptr);
			GLBuffer::unbind(*m_pArrayBuffer);
		}
	};
}



#endif // GRAPHICS_GLATTRIBUTELIST_H_
