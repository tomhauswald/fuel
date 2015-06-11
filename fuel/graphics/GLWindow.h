/*****************************************************************
 **' GLWindow.h
 *****************************************************************
 **' Created on: 11.06.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_GLWINDOW_H_
#define GRAPHICS_GLWINDOW_H_

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLWindowSettings.h"

namespace fuel
{
	using namespace std;
	namespace graphics
	{
		/**
		 * OpenGL window.
		 */
		class GLWindow
		{
		private:
			//Underlying GLFW window
			GLFWwindow *m_pWindow;

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
}


#endif // GRAPHICS_GLWINDOW_H_
