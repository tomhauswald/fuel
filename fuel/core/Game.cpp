/*****************************************************************
 * Game.cpp
 *****************************************************************
 * Created on: 23.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "Game.h"

#define RESOLUTION_X		 	1440
#define RESOLUTION_Y 			810
#define FULLSCREEN				0

namespace fuel
{
	Game::Game(void)
		:m_window({RESOLUTION_X, RESOLUTION_Y, FULLSCREEN}),
		 m_keyboard(m_window),
		 m_projection(glm::perspective(45.0f, RESOLUTION_X / (float)RESOLUTION_Y, 0.1f, 100.0f)),
		 m_deferredFBO(RESOLUTION_X, RESOLUTION_Y),
		 m_pSceneRoot(nullptr),
		 m_sleepTime(0.0f),
		 m_updateTime(0.0f),
		 m_geomRenderTime(0.0f),
		 m_fsRenderTime(0.0f)
	{
		// Seed RNG
		srand(time(nullptr));

		// Move camera
		m_camera.getTransform().setPosition({0, 0, 5});

		// Setup default deferred framebuffer (diffuse, position & normal channels, depth)
		GLFramebuffer::bind(m_deferredFBO);
		m_deferredFBO.attach("diffuse",  GL_RGB32F);
		m_deferredFBO.attach("position", GL_RGB32F);
		m_deferredFBO.attach("normal",   GL_RGB32F);
		m_deferredFBO.attach("depth",    GL_DEPTH_COMPONENT32F);
		m_deferredFBO.setDrawAttachments({"diffuse", "position", "normal"});
		GLFramebuffer::unbind();
	}

	void Game::update(void)
	{
		float startTime = static_cast<float>(glfwGetTime());

		// Regulate FPS
		if(m_updateTime + m_geomRenderTime + m_fsRenderTime < 1.0f / 60)
		{
			sleepSeconds(1.0f / 60 - (m_updateTime + m_geomRenderTime + m_fsRenderTime));
			m_sleepTime = static_cast<float>(glfwGetTime()) - startTime;
		}
		else m_sleepTime = 0.0f;

		// Determine sleep time
		cout << "Sleep:\t\t\t"
			 << 1E3 * (m_sleepTime = static_cast<float>(glfwGetTime()) - startTime)
			 << "ms."
			 << endl;

		startTime += m_sleepTime;

		// Handle input
		if(m_keyboard.wasKeyReleased(GLFW_KEY_ESCAPE))
			m_window.close();
		m_keyboard.update();

		// Update scene
		if(m_pSceneRoot) m_pSceneRoot->update(*this, m_updateTime + m_sleepTime);

		// Determine update time
		cout << "Update:\t\t\t"
			 << 1E3 * (m_updateTime = static_cast<float>(glfwGetTime()) - startTime)
			 << "ms."
			 << endl;
	}

	void Game::prepareGeometryPasses(void)
	{
		GLFramebuffer::bind(m_deferredFBO);

		//Disable blending, enable depth
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		GLFramebuffer::clear();
	}

	void Game::prepareFullscreenPasses(void)
	{
		GLFramebuffer::unbind();
		glClear(GL_COLOR_BUFFER_BIT);

		GLFramebuffer::bind(m_deferredFBO, GLFramebuffer::READ);

		//Disable depth, enable blending
		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);
	}

	void Game::prepareGUIPasses(void)
	{
		GLFramebuffer::bind(m_deferredFBO, GLFramebuffer::READ);

		//Disable blending, enable depth
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		glUseProgram(GL_NONE);
	}

	void Game::render(void)
	{
		float startTime = static_cast<float>(glfwGetTime());

		// Prepare geometry passes
		m_window.prepare();
		this->prepareGeometryPasses();

		// Render scene
		if(m_pSceneRoot) m_pSceneRoot->geometryPass(*this);

		// Determine geometry rendering time
		cout << "Geometry passes:\t"
			 << 1E3 * (m_geomRenderTime = static_cast<float>(glfwGetTime()) - startTime)
			 << "ms."
			 << endl;

		// ---------------------------------------------------------------------

		startTime += m_geomRenderTime;

		// Fullscreen passes
		this->prepareFullscreenPasses();
		if(m_pSceneRoot) m_pSceneRoot->fullscreenPass(*this);

		// GUI passes
		this->prepareGUIPasses();
		if(m_pSceneRoot) m_pSceneRoot->guiPass(*this);

		if(true) // Show gbuffer textures
		{
			// Render downscales gbuffer textures as overlay
			static constexpr uint16_t previewWidth = 160, previewHeight = 90;
			m_deferredFBO.showAttachmentContent("diffuse",    		 0, previewHeight, previewWidth, previewHeight);
			m_deferredFBO.showAttachmentContent("position",   		 0, 		    0, previewWidth, previewHeight);
			m_deferredFBO.showAttachmentContent("normal",   previewWidth,  		    0, previewWidth, previewHeight);
		}

		m_window.display();

		// Determine fullscreen passes rendering time
		cout << "Fullscreen passes:\t"
			 << 1E3 * (m_fsRenderTime = static_cast<float>(glfwGetTime()) - startTime)
			 << "ms."
			 << endl << endl;
	}

	glm::mat4 Game::calculateViewProjectionMatrix(void)
	{
		return m_projection * m_camera.calculateViewMatrix();
	}
}


