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

		// Main camera
		Camera m_camera;

		// Framebuffer object used to render GBuffer textures to
		GLFramebuffer m_deferredFBO;

		// Shader program manager
		ShaderManager m_shaderMgr;

		// Texture manager
		TextureManager m_textureMgr;

		// Fullscreen quad vertices
		GLVertexArray m_fullscreenQuadVAO;

		// Scene root
		shared_ptr<GameComponent> m_pSceneRoot;

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
		 * Renders a fullscreen quad.
		 */
		inline void renderFullscreenQuad(void)
		{
			GLVertexArray::bind(m_fullscreenQuadVAO);
			glDrawArrays(GL_QUADS, 0, 4);
		}

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
		inline shared_ptr<GameComponent> &getSceneRoot(void){ return m_pSceneRoot; }

		/**
		 * Sets the scene root game object.
		 *
		 * @param root
		 * 		The new scene root.
		 */
		inline void setSceneRoot(shared_ptr<GameComponent> &root){ m_pSceneRoot = root; }

		/**
		 * Releases any resources.
		 */
		virtual ~Game(void) = default;
	};
}


#endif // CORE_GAME_H_
