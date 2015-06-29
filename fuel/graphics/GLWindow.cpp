/*****************************************************************
 * GLWindow.cpp
 *****************************************************************
 * Created on: 11.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "GLWindow.h"
#include "../core/Util.h"

namespace fuel
{
	GLWindow::GLWindow(const GLWindowSettings &settings)
		:m_pWindow(nullptr),
		 m_pFullscreenQuadVAO(nullptr)
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
			settings.fullscreen ? glfwGetPrimaryMonitor() : nullptr,
			nullptr
		);

		// Check whether window was created correctly
		if( m_pWindow == nullptr )
		{
			cerr << "Could not create GLFW window." << endl;
		}

		// Center the window
		if(!settings.fullscreen)
		{
			const GLFWvidmode &vidmode = *glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowPos(
				m_pWindow,
				(vidmode.width  - settings.width  ) / 2,
				(vidmode.height - settings.height ) / 2
			);
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
		cout << "GLFW version: " 	<< glfwGetVersionString() << endl;
		cout << "OpenGL version: " 	<< glGetString( GL_VERSION ) << endl;
		cout << "GLSL version: "	<< glGetString( GL_SHADING_LANGUAGE_VERSION ) << endl;
		cout << "GPU Information: " << glGetString( GL_RENDERER ) << endl;

		// Setup some OpenGL states
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_2D);

		glViewport(0, 0, settings.width, settings.height);

		// Setup fullscreen quad VAO
		m_pFullscreenQuadVAO = make_unique<GLVertexArray>(2);
		GLVertexArray::bind(*m_pFullscreenQuadVAO);
		m_pFullscreenQuadVAO->getAttributeList(0).write<float, 2>(GL_STATIC_DRAW, GL_FLOAT,
		{
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f
		});
		m_pFullscreenQuadVAO->getAttributeList(1).write<float, 2>(GL_STATIC_DRAW, GL_FLOAT,
		{
			 0.0f, 0.0f,
			 1.0f, 0.0f,
			 1.0f, 1.0f,
			 0.0f, 1.0f
		});
		GLVertexArray::unbind();
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

	void GLWindow::renderGeometry(GLVertexArray &vao, unsigned verts, GLenum primitive)
	{
		GLVertexArray::bind(vao);
		glDrawArrays(primitive, 0, verts);
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
