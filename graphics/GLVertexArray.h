/*****************************************************************
 * GLVertexArray.h
 *****************************************************************
 * Created on: 11.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_GLVERTEXARRAY_H_
#define GRAPHICS_GLVERTEXARRAY_H_

#include "GLWindow.h"
#include "GLAttributeList.h"
#include <memory>

namespace fuel
{
	namespace graphics
	{
		class GLVertexArray
		{
			private:
				// OpenGL VAO ID
				GLuint m_ID;

				// Stored attribute lists
				vector<GLAttributeList *> m_attributeLists;

			public:
				/**
				 * Instantiates a new OpenGL vertex array object.
				 *
				 * @param attributeListCount
				 *        	Number of attribute lists that will be used.
				 */
				GLVertexArray(uint8_t attributeListCount);

				/**
				 * Returns the ID of this vertex array.
				 *
				 * @return ID.
				 */
				inline GLuint getID(void) const { return m_ID; }

				/**
				 * Returns an attribute list.
				 *
				 * @param id
				 * 			The attribute list ID.
				 * @return Attribute list.
				 */
				inline GLAttributeList &getAttributeList(uint8_t id){ return *m_attributeLists[id]; }

				/**
				 * Binds a vertex array object in order to use it.
				 * Also enables all attribute lists.
				 */
				static void bind(const GLVertexArray &vao);

				/**
				 * Unbinds any vertex array.
				 * Disables all attribute lists.
				 */
				static inline void unbind(void)
				{
					// Disable all vertex attribute lists
					GLint maxAttributeLists;
					glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributeLists);
					for(GLuint attributeList = 0; attributeList < static_cast<GLuint>(maxAttributeLists); ++attributeList)
						glDisableVertexAttribArray(attributeList);
					glBindVertexArray(GL_NONE);
				}

				/**
				 * Unbinds any vertex array.
				 * Disables attribute lists used by the VAO specified.
				 * Prefer this version if you know the currently bound VAO.
				 */
				static inline void unbind(const GLVertexArray &vao)
				{
					// Disable active attribute lists
					for(auto &attributeList : vao.m_attributeLists)
						attributeList->disable();
					glBindVertexArray(GL_NONE);
				}

				/**
				 * Delete the underlying OpenGL VAO.
				 */
				~GLVertexArray(void);
		};
	}
}

#endif // GRAPHICS_GLVERTEXARRAY_H_
