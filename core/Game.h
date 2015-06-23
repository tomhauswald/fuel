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
#include "ShaderManager.h"
#include "../graphics/GLWindow.h"
#include "../graphics/GLVertexArray.h"
#include "../graphics/GLFramebuffer.h"
#include "../graphics/Camera.h"
#include "../input/Keyboard.h"

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

		// Fullscreen quad vertices
		GLVertexArray m_fullscreenQuadVAO;

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
		virtual void init(void);

		/**
		 * Runs the game.
		 */
		inline void run(void)
		{
			// Initialize
			this->init();

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
		 * Returns the window.
		 *
		 * @return Window.
		 */
		inline const GLWindow &getWindow(void) const { return m_window; }

		/**
		 * Returns the camera.
		 *
		 * @return Camera.
		 */
		inline Camera &getCamera(void){ return m_camera; }

		/**
		 * Returns the camera.
		 *
		 * @return Camera.
		 */
		inline const Camera &getCamera(void) const { return m_camera; }

		/**
		 * Releases any resources.
		 */
		virtual ~Game(void);
	};
}


#endif // CORE_GAME_H_
