/*****************************************************************
 **' GLBuffer.cpp
 *****************************************************************
 **' Created on: 11.06.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "GLBuffer.h"

namespace fuel
{
	namespace graphics
	{
		GLBuffer::GLBuffer(GLenum target)
			:m_ID(GL_NONE), m_target(target)
		{
			glGenBuffers(1, &m_ID);
			if(m_ID == GL_NONE)
			{
				cerr << "Could not generate OpenGL buffer." << endl;
			}
			else
			{
				cout << "Generated OpenGL buffer: " << m_ID << endl;
			}
		}

		int GLBuffer::getByteSize(void) const
		{
			int size;
			glGetBufferParameteriv(m_target, GL_BUFFER_SIZE, &size);
			return size;
		}

		void GLBuffer::bind()
		{
			glBindBuffer(m_target, m_ID);
		}

		GLBuffer::~GLBuffer(void)
		{
			// Delete buffer
			if(m_ID != GL_NONE)
			{
				cout << "Deleting OpenGL buffer: " << m_ID << endl;
				glDeleteBuffers(1, &m_ID);
				m_ID = GL_NONE;
			}
		}
	}
}
