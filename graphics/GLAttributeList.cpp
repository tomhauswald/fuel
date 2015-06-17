/*****************************************************************
 * GLAttributeList.cpp
 *****************************************************************
 * Created on: 12.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "../core/Util.h"
#include "GLAttributeList.h"

namespace fuel
{
	namespace graphics
	{
		GLAttributeList::GLAttributeList(uint8_t id)
			:m_ID(id), m_enabled(false)
		{
			cout << "Created OpenGL attribute list: " << (int)m_ID << endl;
			m_pArrayBuffer = core::make_unique<GLBuffer>(GL_ARRAY_BUFFER);
			this->enable();
		}

		void GLAttributeList::enable(void)
		{
			if(!m_enabled)
			{
				glEnableVertexAttribArray(m_ID);
				GLBuffer::bind(*m_pArrayBuffer);
				m_enabled = true;
			}
		}

		void GLAttributeList::disable(void)
		{
			if(m_enabled)
			{
				glDisableVertexAttribArray(m_ID);
				GLBuffer::unbind(*m_pArrayBuffer);
				m_enabled = false;
			}
		}
	}
}
