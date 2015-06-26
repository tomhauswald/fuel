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

namespace fuel
{
	Game::Game(void)
		:m_window({GAME_RESOLUTION_X, GAME_RESOLUTION_Y, GAME_FULLSCREEN}),
		 m_keyboard(m_window),
		 m_projection(glm::perspective(45.0f, GAME_RESOLUTION_X / (float)GAME_RESOLUTION_Y, 0.1f, 100.0f)),
		 m_deferredFBO(GAME_RESOLUTION_X, GAME_RESOLUTION_Y),
		 m_fullscreenQuadVAO(2),
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

		// Setup deferred framebuffer
		GLFramebuffer::bind(m_deferredFBO);
		m_deferredFBO.attach("depth",    GL_DEPTH_COMPONENT32F);
		m_deferredFBO.attach("diffuse",  GL_RGB32F);
		m_deferredFBO.attach("position", GL_RGB32F);
		m_deferredFBO.attach("normal",   GL_RGB32F);
		m_deferredFBO.setDrawAttachments({"diffuse", "position", "normal"});
		GLFramebuffer::unbind();

		// Load default shaders
		// Deferred shader (targeting multiple output textures: gbuffer)
		m_shaderMgr.add("textured", "res/glsl/geometry.vert", "res/glsl/textured.frag");
		{
			auto &sh = m_shaderMgr.get("textured");
			sh.bindVertexAttribute(0, "vPosition");
			sh.bindVertexAttribute(1, "vNormal");
			sh.bindVertexAttribute(2, "vTexCoord");
			sh.link();
			sh.registerUniform("uWVP");
			sh.registerUniform("uWorld");
			sh.registerUniform("uDiffuseTexture");
			sh.getUniform("uDiffuseTexture").set(0);
		}

		// Ambient ligh shader
		m_shaderMgr.add("ambient", "res/glsl/fullscreen.vert", "res/glsl/ambient.frag");
		{
			auto &sh = m_shaderMgr.get("ambient");
			sh.bindVertexAttribute(0, "vPosition");
			sh.bindVertexAttribute(1, "vTexCoord");
			sh.link();
			sh.registerUniform("uDiffuseTexture");
			sh.registerUniform("uColor");
			sh.getUniform("uDiffuseTexture").set(0);
			sh.getUniform("uColor").set(glm::vec3(1.0f, 0.9f, 0.5f) / 16.0f);
		}

		// Directional light shader
		m_shaderMgr.add("directional", "res/glsl/fullscreen.vert", "res/glsl/directional.frag");
		{
			auto &sh = m_shaderMgr.get("directional");
			sh.bindVertexAttribute(0, "vPosition");
			sh.bindVertexAttribute(1, "vTexCoord");
			sh.link();
			sh.registerUniform("uDiffuseTexture");
			sh.registerUniform("uNormalTexture");
			sh.registerUniform("uColor");
			sh.registerUniform("uDirection");
			sh.getUniform("uDiffuseTexture").set(0);
			sh.getUniform("uNormalTexture").set(2);
			sh.getUniform("uColor").set(glm::vec3(1.0f, 0.9f, 0.5f) / 1.75f);
			sh.getUniform("uDirection").set(glm::normalize(glm::vec3(1, -1, -1)));
		}

		// Point light shader
		m_shaderMgr.add("pointlight", "res/glsl/fullscreen.vert", "res/glsl/pointlight.frag");
		{
			auto &sh = m_shaderMgr.get("pointlight");
			sh.bindVertexAttribute(0, "vPosition");
			sh.bindVertexAttribute(1, "vTexCoord");
			sh.link();
			sh.registerUniform("uViewProjection");
			sh.registerUniform("uCameraPosition");
			sh.registerUniform("uDiffuseTexture");
			sh.registerUniform("uPositionTexture");
			sh.registerUniform("uNormalTexture");
			sh.registerUniform("uPosition");
			sh.registerUniform("uColor");
			sh.registerUniform("uRadius");
			sh.registerUniform("uLinearAttenuation");
			sh.registerUniform("uQuadraticAttenuation");
			sh.getUniform("uDiffuseTexture").set(0);
			sh.getUniform("uPositionTexture").set(1);
			sh.getUniform("uNormalTexture").set(2);
		}

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
		if(m_pSceneRoot) m_pSceneRoot->render(*this);

		// Determine geometry rendering time
		cout << "Geometry passes:\t"
			 << 1E3 * (m_geomRenderTime = static_cast<float>(glfwGetTime()) - startTime)
			 << "ms."
			 << endl;

		// ---------------------------------------------------------------------

		startTime += m_geomRenderTime;

		// Prepare fullscreen passes
		this->prepareFullscreenPasses();

		// Ambient light pass
		m_shaderMgr.get("ambient").use();
		this->renderFullscreenQuad();

		// Directional light pass
		m_shaderMgr.get("directional").use();
		for(; false; )
			this->renderFullscreenQuad();

		// Point light passes
		m_shaderMgr.get("pointlight").use();
		for(; false; )
			this->renderFullscreenQuad();

		// GUI passes
		prepareGUIPasses();
		if(m_pSceneRoot) m_pSceneRoot->gui(*this);

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


