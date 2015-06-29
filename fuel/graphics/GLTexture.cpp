/*****************************************************************
 * GLTexture.cpp
 *****************************************************************
 * Created on: 17.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <SOIL.h>
#include "GLTexture.h"

namespace fuel
{
	GLTexture::GLTexture(void)
		:m_ID(GL_NONE), m_width(0), m_height(0)
	{
		// Create empty texture
		glGenTextures(1, &m_ID);

		if(m_ID != GL_NONE)
		{
			cout << "Generated OpenGL texture: " << m_ID << endl;
		}
		else
		{
			cerr << "Could not generate OpenGL texture." << endl;
		}
	}

	GLTexture::GLTexture(const string &filename)
		:m_ID(GL_NONE), m_width(0), m_height(0)
	{
		// Load texture using SOIL
		m_ID = SOIL_load_OGL_texture(filename.c_str(), 4, 0, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

		if(m_ID != GL_NONE)
		{
			cout << "Generated OpenGL texture: " << m_ID << endl;
			cout << "Loaded texture data from: " << filename << endl;

			glBindTexture(GL_TEXTURE_2D, m_ID);

			// Find texture size
			int w, h;
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
			m_width = static_cast<uint16_t>(w);
			m_height = static_cast<uint16_t>(h);

			cout << "Texture size is: " << m_width << "x" << m_height << " pixels." << endl;

			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}
		else
		{
			cerr << "Could not generate OpenGL texture." << endl;
		}
	}

	GLTexture::~GLTexture(void)
	{
		// Delete texture
		if(m_ID != GL_NONE)
		{
			cout << "Deleting OpenGL texture: " << m_ID << endl;
			glDeleteTextures(1, &m_ID);
			m_ID = GL_NONE;
		}
	}
}
