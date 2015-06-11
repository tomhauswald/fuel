/*****************************************************************
 **' GLVertexArray.h
 *****************************************************************
 **' Created on: 11.06.2015
 **' Author: HAUSWALD, Tom.
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
				 * Bind this vertex array object in order to use it.
				 * Also enables all attribute lists.
				 */
				void bind(void);

				/**
				 * Delete the underlying OpenGL VAO.
				 */
				~GLVertexArray(void);
		};
	}
}

#endif // GRAPHICS_GLVERTEXARRAY_H_
