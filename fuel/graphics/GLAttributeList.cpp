/*****************************************************************
 * GLAttributeList.cpp
 *****************************************************************
 * Created on: 12.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <iostream>
#include "../core/Util.h"
#include "GLAttributeList.h"

namespace fuel
{
	using namespace std;

	GLAttributeList::GLAttributeList(GLuint id)
		:m_ID(id)
	{
		cout << "Created OpenGL attribute list: " << m_ID << endl;
		m_pArrayBuffer = make_unique<GLBuffer>(GL_ARRAY_BUFFER);
	}
}
