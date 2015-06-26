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
#define GAME_FULLSCREEN		 	1
#define GAME_CAMERA_POSITION	{0, 0, 5}

namespace fuel
{
	Game::Game(void)
		:m_window({GAME_RESOLUTION_X, GAME_RESOLUTION_Y, GAME_FULLSCREEN}),
		 m_keyboard(m_window),
		 m_deferredFBO(GAME_RESOLUTION_X, GAME_RESOLUTION_Y),
		 m_fullscreenQuadVAO(2)
	{
		// Seed RNG
		srand(time(nullptr));

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
		// Deferred shader (targeting multiple output textures: gbuffer)
		m_shaderMgr.add("deferred", "res/glsl/deferred.vert", "res/glsl/deferred.frag");
		auto &deferredShader = m_shaderMgr.get("deferred");
		deferredShader.bindVertexAttribute(0, "vPosition");
		deferredShader.bindVertexAttribute(1, "vNormal");
		deferredShader.bindVertexAttribute(2, "vTexCoord");
		deferredShader.link();
		deferredShader.registerUniform("uWVP");
		deferredShader.registerUniform("uWorld");
		deferredShader.registerUniform("uDiffuseTexture");
		deferredShader.getUniform("uDiffuseTexture").set(0);

		// Ambient ligh shader
		m_shaderMgr.add("ambient", "res/glsl/fullscreen.vert", "res/glsl/ambient.frag");
		auto &ambientLightShader = m_shaderMgr.get("ambient");
		ambientLightShader.bindVertexAttribute(0, "vPosition");
		ambientLightShader.bindVertexAttribute(1, "vTexCoord");
		ambientLightShader.link();
		ambientLightShader.registerUniform("uDiffuseTexture");
		ambientLightShader.registerUniform("uColor");
		ambientLightShader.getUniform("uDiffuseTexture").set(0);
		ambientLightShader.getUniform("uColor").set(glm::vec3(1.0f, 0.9f, 0.5f) / 16.0f);

		// Directional light shader
		m_shaderMgr.add("directional", "res/glsl/fullscreen.vert", "res/glsl/directional.frag");
		auto &dirLightShader = m_shaderMgr.get("directional");
		dirLightShader.bindVertexAttribute(0, "vPosition");
		dirLightShader.bindVertexAttribute(1, "vTexCoord");
		dirLightShader.link();
		dirLightShader.registerUniform("uDiffuseTexture");
		dirLightShader.registerUniform("uNormalTexture");
		dirLightShader.registerUniform("uColor");
		dirLightShader.registerUniform("uDirection");
		dirLightShader.getUniform("uDiffuseTexture").set(0);
		dirLightShader.getUniform("uNormalTexture").set(2);
		dirLightShader.getUniform("uColor").set(glm::vec3(1.0f, 0.9f, 0.5f) / 1.75f);
		dirLightShader.getUniform("uDirection").set(glm::normalize(glm::vec3(1, -1, -1)));

		// Point light shader
		m_shaderMgr.add("pointlight", "res/glsl/fullscreen.vert", "res/glsl/pointlight.frag");
		auto &pointLightShader = m_shaderMgr.get("pointlight");
		pointLightShader.bindVertexAttribute(0, "vPosition");
		pointLightShader.bindVertexAttribute(1, "vTexCoord");
		pointLightShader.link();
		pointLightShader.registerUniform("uViewProjection");
		pointLightShader.registerUniform("uCameraPosition");
		pointLightShader.registerUniform("uDiffuseTexture");
		pointLightShader.registerUniform("uPositionTexture");
		pointLightShader.registerUniform("uNormalTexture");
		pointLightShader.registerUniform("uPosition");
		pointLightShader.registerUniform("uColor");
		pointLightShader.registerUniform("uRadius");
		pointLightShader.registerUniform("uLinearAttenuation");
		pointLightShader.registerUniform("uQuadraticAttenuation");
		pointLightShader.getUniform("uDiffuseTexture").set(0);
		pointLightShader.getUniform("uPositionTexture").set(1);
		pointLightShader.getUniform("uNormalTexture").set(2);

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
		// Calculate passed time in seconds
		static float lastTime = static_cast<float>(glfwGetTime());
		float time 			  = static_cast<float>(glfwGetTime());
		float dt 			  = time - lastTime;
		lastTime 			  = time;

		if(m_keyboard.wasKeyReleased(GLFW_KEY_ESCAPE))
			m_window.close();
		m_keyboard.update();

		// Update scene
		if(m_pSceneRoot) m_pSceneRoot->update(dt);
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
		// Prepare geometry passes
		m_window.prepare();
		this->prepareGeometryPasses();
		m_shaderMgr.get("deferred").use();

		// Render scene
		if(m_pSceneRoot) m_pSceneRoot->render();

		// Prepare fullscreen passes
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

		// Render GUI passes
		this->prepareGeometryPasses();
		if(m_pSceneRoot) m_pSceneRoot->gui();

		if(true) // Show gbuffer textures
		{
			// Render downscales gbuffer textures as overlay
			static constexpr uint16_t previewWidth = 160, previewHeight = 90;
			m_deferredFBO.showAttachmentContent("diffuse",    		 0, previewHeight, previewWidth, previewHeight);
			m_deferredFBO.showAttachmentContent("position",   		 0, 		    0, previewWidth, previewHeight);
			m_deferredFBO.showAttachmentContent("depth",   previewWidth,  		    0, previewWidth, previewHeight);
		}

		m_window.display();
	}
}


