/*****************************************************************
 * GLVertexArray.h
 *****************************************************************
 * Created on: 11.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_GLVERTEXARRAY_H_
#define GRAPHICS_GLVERTEXARRAY_H_

#include "GLCalls.h"
#include "GLAttributeList.h"
#include <memory>

namespace fuel
{
	/**
	 * Wrapper class for an OpenGL vertex array object. (VAO)
	 */
	class GLVertexArray
	{
		private:
			// OpenGL VAO ID
			GLuint m_ID;

			// Stored attribute lists
			std::vector<GLAttributeList *> m_attributeLists;

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
			 */
			static inline void unbind(void)
			{
				glBindVertexArray(GL_NONE);
			}

			/**
			 * Delete the underlying OpenGL VAO.
			 */
			~GLVertexArray(void);
	};
}

#endif // GRAPHICS_GLVERTEXARRAY_H_
