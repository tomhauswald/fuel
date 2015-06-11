/*****************************************************************
 **' GLAttributeList.cpp
 *****************************************************************
 **' Created on: 12.06.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "GLAttributeList.h"

namespace fuel
{
	namespace graphics
	{
		GLAttributeList::GLAttributeList(uint8_t id)
			:m_ID(id), m_pArrayBuffer(nullptr)
		{
			m_pArrayBuffer.reset(new GLBuffer(GL_ARRAY_BUFFER));
			enable();
		}

		void GLAttributeList::enable(void)
		{
			if(!m_enabled)
			{
				glEnableVertexAttribArray(m_ID);
				m_enabled = true;
			}
		}

		void GLAttributeList::disable(void)
		{
			if(m_enabled)
			{
				glDisableVertexAttribArray(m_ID);
				m_enabled = false;
			}
		}

		GLAttributeList::~GLAttributeList(void)
		{

		}
	}
}
