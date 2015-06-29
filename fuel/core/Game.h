/*****************************************************************
 * Game.h
 *****************************************************************
 * Created on: 23.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef CORE_GAME_H_
#define CORE_GAME_H_

#include <cstdlib>
#include "Util.h"
#include "../mgmt/ShaderManager.h"
#include "../mgmt/TextureManager.h"
#include "../graphics/GLWindow.h"
#include "../graphics/GLVertexArray.h"
#include "../graphics/GLFramebuffer.h"
#include "../graphics/Camera.h"
#include "../input/Keyboard.h"
#include "GameComponent.h"

namespace fuel
{
	class Game
	{
	private:
		// Window
		GLWindow m_window;

		// Keyboard
		Keyboard m_keyboard;

		// Projection matrix
		glm::mat4 m_projection;

		// Main camera
		Camera m_camera;

		// Framebuffer object used to render GBuffer textures to
		GLFramebuffer m_deferredFBO;

		// Shader program manager
		ShaderManager m_shaderMgr;

		// Texture manager
		TextureManager m_textureMgr;

		// Scene root
		GameComponent *m_pSceneRoot;

		// Time slept in seconds
		float m_sleepTime;

		// Time taken for updated in seconds
		float m_updateTime;

		// Time taken for geometry rendering in seconds
		float m_geomRenderTime;

		// Time taken for fullscreen passes in seconds
		float m_fsRenderTime;

		/**
		 * Updates the current scene.
		 */
		void update(void);

		/**
		 * Renders the current scene.
		 */
		void render(void);

		/**
		 * Prepares the renderer for following geometry passes.
		 * This binds the deferred FBO and clears its buffers.
		 * Also enables depth tests and disables blending.
		 */
		void prepareGeometryPasses(void);

		/**
		 * Prepares the renderer for following fullscreen passes.
		 * This binds the default FBO and clears its color buffer.
		 * Also disables depth tests and enables blending.
		 */
		void prepareFullscreenPasses(void);

		/**
		 * Prepares the renderer for following GUI passes.
		 * Binds the deferred FBO for reading and enables depth.
		 */
		void prepareGUIPasses(void);

	public:
		/**
		 * Instantiates a new game.
		 */
		Game(void);

		/**
		 * Perfoms any custom initialization logic.
		 */
		virtual void setup(void) = 0;

		/**
		 * Runs the game.
		 */
		inline void run(void)
		{
			// Initialize
			this->setup();

			// Main loop
			while(!m_window.closed())
			{
				this->update();
				this->render();
			}
		}

		/**
		 * Returns the window.
		 *
		 * @return Window.
		 */
		inline GLWindow &getWindow(void){ return m_window; }

		/**
		 * Returns the camera.
		 *
		 * @return Camera.
		 */
		inline Camera &getCamera(void){ return m_camera; }

		/**
		 * Returns the keyboard.
		 *
		 * @return Keyboard.
		 */
		inline Keyboard &getKeyboard(void){ return m_keyboard; }

		/**
		 * Returns the texture manager.
		 *
		 * @return Texture manager.
		 */
		inline TextureManager &getTextureManager(void){ return m_textureMgr; }

		/**
		 * Returns the shader manager.
		 *
		 * @return Shader manager.
		 */
		inline ShaderManager &getShaderManager(void){ return m_shaderMgr; }

		/**
		 * Returns the scene root game object.
		 *
		 * @return Scene root.
		 */
		inline GameComponent &getSceneRoot(void){ return *m_pSceneRoot; }

		/**
		 * Sets the scene root game object.
		 *
		 * @param root
		 * 		The new scene root.
		 */
		inline void setSceneRoot(GameComponent *root){ m_pSceneRoot = root; }

		/**
		 * Returns the projection matrix.
		 *
		 * @return
		 * 		The projection matrix.
		 */
		inline const glm::mat4 &getProjectionMatrix(void) const{ return m_projection; }

		/**
		 * Sets the projection matrix.
		 *
		 * @param projection
		 *		New projection matrix.
		 */
		inline void setProjectionMatrix(const glm::mat4 &projection){ m_projection = projection; }

		/**
		 * Returns the view-projection-matrix.
		 *
		 * @return
		 *		View-projection-matrix. (P x V)
		 */
		glm::mat4 calculateViewProjectionMatrix(void);

		/**
		 * Releases any resources and destroy scene root.
		 */
		virtual ~Game(void) = default;
	};
}


#endif // CORE_GAME_H_
