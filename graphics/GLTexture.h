/*****************************************************************
 * GLTexture.h
 *****************************************************************
 * Created on: 17.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_GLTEXTURE_H_
#define GRAPHICS_GLTEXTURE_H_

#include "GLWindow.h"
#include <vector>

namespace fuel
{
	/**
	 * Wrapper class for OpenGL textures.
	 * Also provides methods to load textures from various
	 * file formats. (using the Simple OpenGL image loader library)
	 */
	class GLTexture
	{
	private:
		// OpenGL texture ID
		GLuint m_ID;

		// Texture width
		uint16_t m_width;

		// Texture height
		uint16_t m_height;

	public:
		/**
		 * Instantiates a new empty OpenGL texture.
		 */
		GLTexture(void);

		/**
		 * Loads an OpenGL texture from a file.
		 *
		 * @param filename
		 * 		File to load the texture from.
		 */
		GLTexture(const string &filename);

		/**
		 * Returns the OpenGL texture ID.
		 *
		 * @return Texture ID.
		 */
		inline GLuint getID(void) const { return m_ID; }

		/**
		 * Returns the texture width in pixels.
		 *
		 * @return Width.
		 */
		inline uint16_t getWidth(void) const { return m_width; }

		/**
		 * Returns the texture height in pixels.
		 *
		 * @return Height.
		 */
		inline uint16_t getHeight(void) const { return m_height; }

		/**
		 * Binds the given texture to the GL_TEXTURE_2D target of the texture unit specified.
		 *
		 * @param unit
		 * 		Texture unit to bind texture to.
		 *
		 * @param txr
		 * 		Texture to bind.
		 */
		static inline void bind(GLint unit, const GLTexture &txr)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, txr.m_ID);
		}

		/**
		 * Unbinds any texture from the GL_TEXTURE_2D target of the texture unit specified.
		 *
		 * @param unit
		 * 		Texture unit to unbind texture from.
		 */
		static inline void unbind(GLint unit){ glActiveTexture(GL_TEXTURE0 + unit); glBindTexture(GL_TEXTURE_2D, GL_NONE); }

		/**
		 * Unbinds any texture from the GL_TEXTURE_2D target of the texture units specified.
		 *
		 * @param units
		 * 		Vector containing texture unit IDs to unbind textures from.
		 */
		static inline void unbind(const vector<GLint> &units)
		{
			for(GLint unit : units)
				unbind(unit);
		}

		/**
		 * Delete the OpenGL texture object.
		 */
		~GLTexture(void);
	};
}


#endif // GRAPHICS_GLTEXTURE_H_
