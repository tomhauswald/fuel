/*****************************************************************
 * GLWindow.cpp
 *****************************************************************
 * Created on: 11.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "GLWindow.h"

namespace fuel
{
	namespace graphics
	{
		GLWindow::GLWindow(const GLWindowSettings &settings)
			:m_pWindow(nullptr)
		{
			// Try to initialize GLFW
			if( glfwInit() != GL_TRUE )
			{
				cerr << "Could not initialize GLFW." << endl;
			}

			// Setup window properties
			glfwWindowHint( GLFW_VISIBLE, 	GL_FALSE );
			glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

			// Create window
			m_pWindow = glfwCreateWindow(
				settings.width,
				settings.height,
				settings.title.c_str(),
				nullptr,
				nullptr
			);

			// Check whether window was created correctly
			if( m_pWindow == nullptr )
			{
				cerr << "Could not create GLFW window." << endl;
			}

			// Get the resolution of the primary monitor
			const GLFWvidmode *pVidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			// Center the window
			glfwSetWindowPos(
				m_pWindow,
				(pVidmode->width - settings.width ) / 2,
				(pVidmode->height - settings.height ) / 2
			);

			// Enable vertical synchronization
			if( settings.vsync )
			{
				glfwSwapInterval( 1 );
			}

			// Make the window visible
			glfwShowWindow( m_pWindow );

			// Make the OpenGL context current
			glfwMakeContextCurrent( m_pWindow );

			// Init GLEW
			glewExperimental = true;
			glewInit();

			// Print context information
			cout << "Successfully created " << settings.width << "x" << settings.height << " window." << endl;
			cout << "GLFW version: " << glfwGetVersionString() << endl;
			cout << "OpenGL version: " << glGetString( GL_VERSION ) << endl;
			cout << "GLSL version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << endl;
			cout << "GPU Information: " << glGetString( GL_RENDERER ) << endl;

			// Setup some OpenGL states
			glEnable( GL_DEPTH_TEST );
			glDepthFunc( GL_LESS );
			glEnable(GL_CULL_FACE);
			glCullFace( GL_BACK );
		}

		uint16_t GLWindow::getWidth(void) const
		{
			int width;
			glfwGetWindowSize(m_pWindow, &width, nullptr);
			return static_cast<uint16_t>(width);
		}

		uint16_t GLWindow::getHeight(void) const
		{
			int height;
			glfwGetWindowSize(m_pWindow, nullptr, &height);
			return static_cast<uint16_t>(height);
		}

		void GLWindow::prepare(void)
		{
			// No window open
			if( m_pWindow == nullptr ) return;

			// This line is critical for LWJGL's interoperation with GLFW's
			// OpenGL context, or any context that is managed externally.
			// LWJGL detects the context that is current in the current thread,
			// creates the ContextCapabilities instance and makes the OpenGL
			// bindings available for use.
			glfwMakeContextCurrent(m_pWindow);

			// Set the clear color to black
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

			// Clear the back buffer
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			// Poll for window events
			glfwPollEvents();
		}

		void GLWindow::display(void)
		{
			// No window open
			if( m_pWindow == nullptr ) return;

			// Advance the back buffer chain
			glfwSwapBuffers( m_pWindow );
		}

		GLWindow::~GLWindow(void)
		{
			if(m_pWindow != nullptr)
			{
				glfwDestroyWindow(m_pWindow);
				m_pWindow = nullptr;
			}

			cout << "Destroyed window." << endl;
		}
	}
}
