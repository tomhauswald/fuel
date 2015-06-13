/*****************************************************************
 * GLFramebuffer.cpp
 *****************************************************************
 * Created on: 13.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "GLFramebuffer.h"

namespace fuel
{
	namespace graphics
	{
		GLFramebuffer::GLFramebuffer(uint16_t width, uint16_t height)
			:m_ID(GL_NONE), m_width(width), m_height(height), m_colorAttachmentCount(0)
		{
			glGenFramebuffers(1, &m_ID);

			if(m_ID == GL_NONE)
			{
				cerr << "Could not generate OpenGL framebuffer." << endl;
			}
			else
			{
				cout << "Generated OpenGL framebuffer: " << m_ID << endl;
			}
		}

		GLenum GLFramebuffer::getColorFormat(GLenum txrFormat)
		{
			if(txrFormat == GL_RGB32F || txrFormat == GL_RGB32UI) return GL_RGB;
			if(txrFormat == GL_RGBA32F || txrFormat == GL_RGBA32UI) return GL_RGBA;
			if(txrFormat == GL_DEPTH_COMPONENT32F) return GL_DEPTH_COMPONENT;
			return GL_NONE;
		}

		GLenum GLFramebuffer::getDatatype(GLenum txrFormat)
		{
			if(txrFormat == GL_RGB32F || txrFormat == GL_RGBA32F || txrFormat == GL_DEPTH_COMPONENT32F) return GL_FLOAT;
			if(txrFormat == GL_RGB32UI || txrFormat == GL_RGBA32UI) return GL_UNSIGNED_INT;
			return GL_NONE;
		}

		GLenum GLFramebuffer::findAttachmentSlot(GLenum txrFormat)
		{
			if(txrFormat == GL_DEPTH_COMPONENT32F) return GL_DEPTH_ATTACHMENT;
			else return GL_COLOR_ATTACHMENT0 + m_colorAttachmentCount;
		}

		void GLFramebuffer::attach(const string &attachment, GLenum txrFormat)
		{
			GLenum colorFormat, datatype;
			if((colorFormat = getColorFormat(txrFormat)) == GL_NONE || (datatype = getDatatype(txrFormat)) == GL_NONE)
			{
				cerr << "Invalid texture format specified." << endl;
				cerr << "Should be one of: GL_RGB32(F/UI), GL_RGBA32(F/UI), GL_DEPTH_COMPONENT32F." << endl;
				return;
			}

			// Get FBO attachment slot for the new texture
			GLenum slot = findAttachmentSlot(txrFormat);

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, txrFormat, m_width, m_height, 0, colorFormat, datatype, nullptr);
			glFramebufferTexture2D(GL_FRAMEBUFFER, slot, GL_TEXTURE_2D, texture, 0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);

			// Construct new FBO attachment
			GLFramebufferAttachment fboAttachment;
			fboAttachment.name = attachment;
			fboAttachment.texture = texture;
			fboAttachment.textureFormat = txrFormat;
			fboAttachment.colorFormat = colorFormat;
			fboAttachment.datatype = datatype;
			fboAttachment.attachmentSlot = slot;

			m_attachments.insert({attachment, fboAttachment});

			// Increment color attachment count if neccessary
			if(txrFormat != GL_DEPTH_COMPONENT32F) m_colorAttachmentCount++;
		}

		void GLFramebuffer::setDrawAttachments(const vector<string> &attachments)
		{
			vector<GLenum> buffers;
			for(unsigned i=0; i<attachments.size(); ++i)
				buffers.push_back(m_attachments[attachments[i]].attachmentSlot);

			glDrawBuffers(buffers.size(), &buffers[0]);
		}

		GLFramebuffer::~GLFramebuffer(void)
		{
			// Delete attachment textures
			for(const auto &attachment : m_attachments)
			{
				if(attachment.second.texture != GL_NONE)
				{
					glDeleteTextures(1, &attachment.second.texture);
				}
			}
			m_attachments.clear();

			// Delete FBO itself
			if(m_ID != GL_NONE)
			{
				cout << "Deleting OpenGL framebuffer: " << m_ID << endl;
				glDeleteFramebuffers(1, &m_ID);
				m_ID = GL_NONE;
			}
		}
	}
}
