/*****************************************************************
 * GLCalls.h
 *****************************************************************
 * Created on: 14.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef GRAPHICS_GLCALLS_H_
#define GRAPHICS_GLCALLS_H_

/**
 * This header includes all OpenGL specific dependencies:
 * 		-	GLEW for extension handling
 * 		-	GLFW for context creation
 *		-	GLM for matrix and vector operations
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef __DEBUG__
	#define __NO_INLINE__
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/random.hpp>
#undef __NO_INLINE__

constexpr float PI = 3.14159265359f;

#endif // GRAPHICS_GLCALLS_H_
