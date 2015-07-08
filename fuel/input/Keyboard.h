/*****************************************************************
 * Keyboard.h
 *****************************************************************
 * Created on: 13.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef INPUT_KEYBOARD_H_
#define INPUT_KEYBOARD_H_

namespace fuel
{
	// Forward declare
	class GLWindow;

	/**
	 * Keyboard handler class.
	 */
	class Keyboard
	{
	private:
		// Keystate array size
		static const unsigned NUM_KEYS = 400;

		// Most recently instantiated keyboard
		static Keyboard *s_pKeyboard;

		// Current key states
		bool m_keys[NUM_KEYS];

		// Previous key states
		bool m_prevKeys[NUM_KEYS];

		// Parent window reference
		GLWindow &m_window;

	public:
		/**
		 * Instantiates a new keyboard handler object and registers
		 * the key callback with the given window.
		 */
		Keyboard(GLWindow &window);

		/**
		 * Returns whether the specified key is currently held down.
		 *
		 * @param key
		 * 		The key.
		 *
		 * @return Whether the key is down.
		 */
		inline bool isKeyDown(int key) const { return m_keys[key]; }

		/**
		 * Returns whether the specified key is currently not held down.
		 *
		 * @param key
		 * 		The key.
		 *
		 * @return Whether the key is up.
		 */
		inline bool isKeyUp(int key) const { return !m_keys[key]; }

		/**
		 * Returns whether the specified key was recently pressed.
		 *
		 * @param key
		 * 		The key.
		 *
		 * @return Whether the key was pressed.
		 */
		inline bool wasKeyPressed(int key) const { return m_keys[key] && !m_prevKeys[key]; }

		/**
		 * Whether the specified key was recently released.
		 *
		 * @param key
		 * 		The key.
		 *
		 * @return Whether the key was released.
		 */
		inline bool wasKeyReleased(int key) const { return !m_keys[key] && m_prevKeys[key]; }

		/**
		 * Updates the key states.
		 */
		inline void update(void)
		{
			for(unsigned k=0; k<NUM_KEYS; ++k)
				m_prevKeys[k] = m_keys[k];
		}

		/**
		 * Unregisters the window's key callback.
		 */
		~Keyboard(void);
	};
}

#endif // INPUT_KEYBOARD_H_
