/*****************************************************************
 **' GLVertexArray.cpp
 *****************************************************************
 **' Created on: 12.06.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "GLVertexArray.h"
#include "../core/Util.h"

namespace fuel
{
	namespace graphics
	{
		GLVertexArray::GLVertexArray(uint8_t attributeListCount)
			:m_ID(GL_NONE), m_attributeLists({})
		{
			glGenVertexArrays(1, &m_ID);

			if(m_ID == GL_NONE)
			{
				cerr << "Could not generate OpenGL vertex array." << endl;
			}
			else
			{
				cout << "Generated OpenGL vertex array: " << m_ID << endl;

				// Generate attribute lists
				for(unsigned attr=0; attr<attributeListCount; attr++)
				{
					m_attributeLists.push_back(new GLAttributeList(attr));
				}
			}
		}

		void GLVertexArray::bind(void)
		{
			glBindVertexArray(m_ID);
		}

		GLVertexArray::~GLVertexArray(void)
		{
			// Delete attribute lists
			for(auto &attributeList : m_attributeLists)
				delete attributeList;
			m_attributeLists.clear();

			// Delete VAO
			if(m_ID != GL_NONE)
			{
				cout << "Deleting OpenGL vertex array: " << m_ID << endl;
				glDeleteVertexArrays(1, &m_ID);
				m_ID = GL_NONE;
			}
		}
	}
}
