/*****************************************************************
 * GLWindow.h
 *****************************************************************
 * Created on: 11.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_GLWINDOW_H_
#define GRAPHICS_GLWINDOW_H_

#include <iostream>
#include "GLVertexArray.h"
#include "GLWindowSettings.h"

namespace fuel
{
	using namespace std;

	/**
	 * Wrapper class for an OpenGL window created and handled by GLFW.
	 */
	class GLWindow
	{
	private:
		//Underlying GLFW window
		GLFWwindow *m_pWindow;

		// Fullscreen quad vertices
		std::unique_ptr<GLVertexArray> m_pFullscreenQuadVAO;

	public:
		/**
		 * Instantiates a new OpenGL window using the given settings.
		 *
		 * @param settings
		 * 			Window settings.
		 */
		GLWindow(const GLWindowSettings &settings);

		/**
		 * Returns the underlying GLFW window handle.
		 *
		 * @return GLFW window handle.
		 */
		inline GLFWwindow *getWindowHandle(void) const { return m_pWindow; }

		/**
		 * Returns whether this window was closed.
		 *
		 * @return Whether the window was closed.
		 */
		inline bool closed() const { return (glfwWindowShouldClose(m_pWindow) == GL_TRUE); }

		/**
		 * Returns the width of the window in pixels.
		 *
		 * @return Width of the window in pixels.
		 */
		uint16_t getWidth(void) const;

		/**
		 * Returns the height of the window in pixels.
		 *
		 * @return Height of the window in pixels.
		 */
		uint16_t getHeight(void) const;

		/**
		 * Tells the window to close.
		 */
		inline void close(void){ glfwSetWindowShouldClose(m_pWindow, GL_TRUE); }

		/**
		 * Renders geometry using a vertex array and an index buffer.
		 *
		 * @param vao
		 * 		Vertex array.
		 *
		 * @param ibo
		 * 		Index buffer.
		 *
		 * @param glIndexType
		 * 		OpenGL type identifier of indices.
		 *
		 * @param primitive
		 * 		Primitive type.
		 *
		 * @param INDEX_TYPE
		 * 		Type of the index buffer elements.
		 */
		template<typename INDEX_TYPE>
		void renderGeometry(GLVertexArray &vao, GLBuffer &ibo, GLenum glIndexType, GLenum primitive = GL_TRIANGLES)
		{
			GLVertexArray::bind(vao);
			GLBuffer::bind(ibo);
			glDrawElements(primitive, ibo.getElementCount<INDEX_TYPE>(), glIndexType, nullptr);
		}

		/**
		 * Renders geometry using a vertex array.
		 *
		 * @param vao
		 * 		Vertex array.
		 *
		 * @param verts
		 * 		Number of vertices.
		 *
		 * @param primitive
		 *		Primitive type.
		 */
		void renderGeometry(GLVertexArray &vao, unsigned verts, GLenum primitive = GL_TRIANGLES);

		/**
		 * Renders a fullscreen quad.
		 */
		inline void renderFullscreenQuad(void){ renderGeometry(*m_pFullscreenQuadVAO, 4, GL_QUADS); }

		/**
		 * Prepares the window to draw the next frame.
		 */
		void prepare(void);

		/**
		 * Draws the next frame.
		 */
		void display(void);

		/**
		 * Delete the underlying GLFW window object.
		 */
		~GLWindow(void);
	};
}


#endif // GRAPHICS_GLWINDOW_H_
