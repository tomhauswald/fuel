/*****************************************************************
 * GLBuffer.h
 *****************************************************************
 * Created on: 11.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_GLBUFFER_H_
#define GRAPHICS_GLBUFFER_H_

#include "GLCalls.h"
#include <vector>

namespace fuel
{
	/*****************************************************************
	 * Wrapper class for generic OpenGL buffers.
	 * This includes:
	 *		- Array buffers (VBOs)
	 *	 	- Element buffers (IBOs)
	 *	 	- etc...
	 *****************************************************************/
	class GLBuffer
	{
	private:
		// OpenGL buffer ID
		GLuint m_ID;

		// OpenGL buffer target
		GLenum m_target;

		// Is this buffer currently bound to the target?
		bool m_bound;

	public:
		/**
		 * Instantiates a new GL buffer.
		 *
		 * @param target
		 *        OpenGL buffer target value. (GL_ARRAY_BUFFER, ..)
		 */
		GLBuffer(GLenum target);

		/**
		 * Returns the buffer ID.
		 *
		 * @return ID.
		 */
		inline int getID(void) const { return m_ID; }

		/**
		 * Returns the size of this buffer in bytes.
		 * This will bind this buffer.
		 *
		 * @return Buffer size in bytes.
		 */
		int getByteSize(void) const;

		/**
		 * Returns the number of elements stored inside this buffer,
		 * given that it stores elements of type T.
		 *
		 * @return Element count.
		 */
		template<typename T>
		int getElementCount(void) const
		{
			return getByteSize() / sizeof(T);
		}

		/**
		 * Binds a buffer in order to use it.
		 *
		 * @param buffer
		 * 		The buffer to bind.
		 */
		static inline void bind(GLBuffer &buffer)
		{
			glBindBuffer(buffer.m_target, buffer.m_ID);
			buffer.m_bound = true;
		}

		/**
		 * Unbind the currently bound buffer from the target.
		 *
		 * @param buffer
		 * 		Buffer that has the correct OpenGL buffer target.
		 */
		static inline void unbind(GLBuffer &buffer)
		{
			glBindBuffer(buffer.m_target, GL_NONE);
			buffer.m_bound = false;
		}

		/**
		 * Write data to this buffer.
		 * This will bind the buffer.
		 *
		 * @param usage
		 *        OpenGL usage value. (GL_STATIC_DRAW, ..)
		 * @param data
		 *        Data as readonly vector reference.
		 */
		template<typename T>
		void write(GLenum usage, const std::vector<T> &data)
		{
			// Ensure the buffer is bound
			if(!m_bound){ GLBuffer::bind(*this); }
			glBufferData(m_target, data.size() * sizeof(T), (const GLvoid *)&data[0], usage);
		}

		/**
		 * Delete OpenGL buffer.
		 */
		~GLBuffer(void);
	};
}

#endif // GRAPHICS_GLBUFFER_H_
