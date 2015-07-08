/*****************************************************************
 * Keyboard.cpp
 *****************************************************************
 * Created on: 13.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <cstring>
#include "Keyboard.h"
#include "../graphics/GLWindow.h"

namespace fuel
{
	Keyboard *Keyboard::s_pKeyboard = nullptr;

	Keyboard::Keyboard(GLWindow &window)
		:m_window(window)
	{
		s_pKeyboard = this;

		// Initialize key states to false
		memset(&m_keys, 	GL_FALSE, NUM_KEYS);
		memset(&m_prevKeys, GL_FALSE, NUM_KEYS);

		// Set window callback
		glfwSetKeyCallback(m_window.getWindowHandle(), [](GLFWwindow* window, int key, int scan, int action, int mods)
		{
			// Update key state accordingly
			s_pKeyboard->m_keys[key] = (action == GLFW_PRESS ? true : false);
		});
	}

	Keyboard::~Keyboard(void)
	{
		// Unset key callback
		glfwSetKeyCallback(m_window.getWindowHandle(), [](GLFWwindow* window, int key, int scan, int action, int mods){ ; });
	}
}
