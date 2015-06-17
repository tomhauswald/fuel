/*****************************************************************
 * GLFramebuffer.h
 *****************************************************************
 * Created on: 13.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_GLFRAMEBUFFER_H_
#define GRAPHICS_GLFRAMEBUFFER_H_

#include "GLWindow.h"
#include <map>
#include <string>
#include <vector>

namespace fuel
{
	/**
	 * Structure that holds all information about an OpenGL framebuffer
	 * attachment texture.
	 */
	struct GLFramebufferAttachment
	{
		// Attachment name
		string name;

		// OpenGL texture ID
		GLuint texture;

		// OpenGL texture format
		GLenum textureFormat;

		// OpenGL pixel value format
		GLenum colorFormat;

		// OpenGL pixel value datatype
		GLenum datatype;

		// Framebuffer attachment ID
		GLenum attachmentSlot;
	};

	/**
	 * Wrapper class for an OpenGL framebuffer object. (FBO)
	 */
	class GLFramebuffer
	{
	private:
		// OpenGL FBO ID
		GLuint m_ID;

		// Framebuffer attachment texture width
		uint16_t m_width;

		// Framebuffer attachment texture height
		uint16_t m_height;

		// Attachment information
		map<string, GLFramebufferAttachment> m_attachments;

		/**
		 * Number of color attachments bound
		 * Used to determine the FBO attachment slot for new textures
		 */
		uint8_t m_colorAttachmentCount;

	public:
		/**
		 * Instantiates a new OpenGL framebuffer.
		 *
		 * @param width
		 *        Framebuffer texture width.
		 * @param height
		 *        Framebuffer texture height.
		 */
		GLFramebuffer(uint16_t width, uint16_t height);

		/**
		 * Returns the ID of this FBO.
		 *
		 * @return OpenGL FBO ID.
		 */
		inline GLuint getID(void) const { return m_ID; }

		/**
		 * Returns the framebuffer texture width.
		 *
		 * @return FBO texture width.
		 */
		inline uint16_t getWidth(void) const { return m_width; }

		/**
		 * Returns the framebuffer texture height.
		 *
		 * @return FBO texture height.
		 */
		inline uint16_t getHeight(void) const { return m_height; }

		/**
		 * Clears color and depth buffer of this framebuffer.
		 */
		inline void clear(void) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

		/**
		 * Returns the number of attachment textures.
		 *
		 * @return Number of attachment textures.
		 */
		inline uint8_t getAttachmentCount(void) const
		{
			return static_cast<uint8_t>(m_attachments.size());
		}

		/**
		 * Binds this FBO to use it.
		 */
		static inline void bind(const GLFramebuffer &fbo){ glBindFramebuffer(GL_FRAMEBUFFER, fbo.m_ID); }

		/**
		 * Unbinds any FBO.
		 */
		static inline void unbind(void){ glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE); }

		/**
		 * Returns the color format corresponding to the specified texture format.
		 *
		 * @param txrFormat
		 * 		Texture format.
		 *
		 * @return Associated color format. GL_NONE if the format was invalid.
		 */
		static GLenum getColorFormat(GLenum txrFormat);

		/**
		 * Returns the datatype corresponding to the specified texture format.
		 *
		 * @param txrFormat
		 * 		Texture format.
		 *
		 * @return Associated datatype. GL_NONE if the format was invalid.
		 */
		static GLenum getDatatype(GLenum txrFormat);

		/**
		 * Returns the FBO attachment slot to use for the new texture.
		 *
		 * @param txrFormat
		 * 		Texture format.
		 *
		 * @return FBO attachment slot.
		 */
		GLenum findAttachmentSlot(GLenum txrFormat);

		/**
		 * Adds an FBO attachment texture to this framebuffer.
		 *
		 * @param attachment
		 * 		Name of the attachment texture.
		 *
		 * @param txrFormat
		 * 		OpenGL attachment format enumeration value (GL_RGB32F,
		 */
		void attach(const string &attachment, GLenum txrFormat);

		/**
		 * Returns information about the framebuffer attachment.
		 *
		 * @param attachment
		 * 		Name of the attachment texture.
		 *
		 * @return OpenGL texture ID.
		 */
		inline const GLFramebufferAttachment &getAttachment(const string &attachment)
		{
			return m_attachments[attachment];
		}

		/**
		 * Specifiy the attachment textures to bind as draw buffers.
		 *
		 * @param attachments
		 * 		Names of the attachment textures to use.
		 */
		void setDrawAttachments(const vector<string> &attachments);

		/**
		 * Renders the content of the specified attachment to the currently bound FBO.
		 *
		 * @param attachment
		 * 		Which attachment texture to show.
		 *
		 * @param x
		 * 		X coordinate. (screenspace)
		 *
		 * @param y
		 * 		Y coordinate. (screenspace)
		 *
		 * @param w
		 * 		Destination width in pixels.
		 *
		 * @param h
		 * 		Destination height in pixels.
		 */
		void showAttachmentContent(const string &attachment, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

		/**
		 * Deletes the attachment textures.
		 */
		~GLFramebuffer(void);
	};
}

#endif // GRAPHICS_GLFRAMEBUFFER_H_
