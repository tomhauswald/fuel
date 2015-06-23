/*****************************************************************
 * Game.cpp
 *****************************************************************
 * Created on: 23.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "Game.h"

#define GAME_RESOLUTION_X 		1600
#define GAME_RESOLUTION_Y  		900
#define GAME_FULLSCREEN		 	0
#define GAME_CAMERA_POSITION	{0, 0, 5}

namespace fuel
{
	Game::Game(void)
		:m_window({GAME_RESOLUTION_X, GAME_RESOLUTION_Y, GAME_FULLSCREEN}),
		 m_keyboard(m_window),
		 m_deferredFBO(GAME_RESOLUTION_X, GAME_RESOLUTION_Y),
		 m_fullscreenQuadVAO(2)
	{
		// Move camera
		m_camera.getTransform().setPosition(GAME_CAMERA_POSITION);

		// Setup deferred framebuffer
		GLFramebuffer::bind(m_deferredFBO);
		m_deferredFBO.attach("depth",    GL_DEPTH_COMPONENT32F);
		m_deferredFBO.attach("diffuse",  GL_RGB32F);
		m_deferredFBO.attach("position", GL_RGB32F);
		m_deferredFBO.attach("normal",   GL_RGB32F);
		m_deferredFBO.setDrawAttachments({"diffuse", "position", "normal"});
		GLFramebuffer::unbind();

		// Load default shaders
		m_shaderMgr.add("deferred",		"res/glsl/deferred.vert", 		"res/glsl/deferred.frag");
		m_shaderMgr.add("ambient",  	"res/glsl/fullscreen.vert", 	"res/glsl/ambient.frag");
		m_shaderMgr.add("directional", 	"res/glsl/fullscreen.vert", 	"res/glsl/directional.frag");
		m_shaderMgr.add("pointlight", 	"res/glsl/fullscreen.vert", 	"res/glsl/pointlight.frag");

		// Setup fullscreen quad VAO
		GLVertexArray::bind(m_fullscreenQuadVAO);
		m_fullscreenQuadVAO.getAttributeList(0).write<float, 2>(GL_STATIC_DRAW, GL_FLOAT,
		{
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f
		});
		m_fullscreenQuadVAO.getAttributeList(1).write<float, 2>(GL_STATIC_DRAW, GL_FLOAT,
		{
			 0.0f, 0.0f,
			 1.0f, 0.0f,
			 1.0f, 1.0f,
			 0.0f, 1.0f
		});
		GLVertexArray::unbind();
	}

	void Game::init(void)
	{
		;;
	}

	void Game::update(void)
	{
		if(m_keyboard.wasKeyReleased(GLFW_KEY_ESCAPE))
			m_window.close();
		m_keyboard.update();

		// Update scene
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

		//Disable depth, enable blending
		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		GLFramebuffer::clear();
	}

	void Game::render(void)
	{
		m_window.prepare();
		this->prepareGeometryPasses();
		m_shaderMgr.get("deferred").use();

		///
		/// Render scene geometry passes
		///

		this->prepareFullscreenPasses();

		// Ambient light pass
		m_shaderMgr.get("ambient").use();
		this->renderFullscreenQuad();

		// Directional light pass
		m_shaderMgr.get("directional").use();
		this->renderFullscreenQuad();

		// Point light passes
		m_shaderMgr.get("pointlight").use();
		this->renderFullscreenQuad();

		if(true) // Show gbuffer textures
		{
			this->prepareGeometryPasses();

			// Render downscales gbuffer textures as overlay
			static constexpr uint16_t previewWidth = 160, previewHeight = 90;
			m_deferredFBO.showAttachmentContent("diffuse",    		 0, previewHeight, previewWidth, previewHeight);
			m_deferredFBO.showAttachmentContent("position",   		 0, 		    0, previewWidth, previewHeight);
			m_deferredFBO.showAttachmentContent("depth",   previewWidth,  		    0, previewWidth, previewHeight);
		}

		m_window.display();
	}

	Game::~Game(void)
	{

	}
}


