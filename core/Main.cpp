/*****************************************************************
 **' Main.cpp
 *****************************************************************
 **' Created on: 11.06.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "Util.h"
#include "../graphics/GLWindow.h"
#include "../graphics/GLVertexArray.h"
#include "../graphics/GLFramebuffer.h"
#include "../graphics/shaders/GLShaderProgram.h"
#include "../input/Keyboard.h"

using namespace std;
using namespace fuel;
using namespace core;
using namespace graphics;
using namespace shaders;
using namespace input;

int main(int argc, char **argv)
{
	GLWindow window({1280, 720, false, true});
	Keyboard keyboard(window);


	// Vertex array
	GLVertexArray vao(2);
	GLVertexArray::bind(vao);

	// Positions
	vao.getAttributeList(0).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT,
	{
			// Front face
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,

			// Right face
			1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,

			// Back face
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,

			// Left face
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,

			// Top Face
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,

			// Bottom Face
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f
	});

	// RGB colors
	vao.getAttributeList(1).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT,
	{
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,

			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,

			1, 1, 0,
			1, 1, 0,
			1, 1, 0,
			1, 1, 0,

			0, 1, 1,
			0, 1, 1,
			0, 1, 1,
			0, 1, 1,

			1, 0, 1,
			1, 0, 1,
			1, 0, 1,
			1, 0, 1,
	});
	GLVertexArray::unbind();


	// Index buffer
	GLBuffer ibo(GL_ELEMENT_ARRAY_BUFFER);
	ibo.write(GL_STATIC_DRAW, vector<uint16_t>
	{
		// Front face
		0, 1, 2, 2, 3, 0,

		// Right face
		7, 6, 5, 5, 4, 7,

		// Back face
		11, 10, 9, 9, 8, 11,

		// Left face
		15, 14, 13, 13, 12, 15,

		// Top Face
		19, 18, 17, 17, 16, 19,

		// Bottom Face
		23, 22, 21, 21, 20, 23
	});
	GLBuffer::unbind(ibo);


	/* Framebuffer
	GLFramebuffer fbo(window.getWidth(), window.getHeight());
	GLFramebuffer::bind(fbo);
	fbo.attach("depth", GL_DEPTH_COMPONENT32F);
	fbo.attach("diffuse", GL_RGB32F);
	fbo.attach("normal", GL_RGB32F);
	fbo.setDrawAttachments({"diffuse", "normal"});
	GLFramebuffer::unbind(); */


	GLShaderProgram shader;
	shader.setShader(EGLShaderType::VERTEX,   "res/glsl/colored.vert");
	shader.setShader(EGLShaderType::FRAGMENT, "res/glsl/colored.frag");
	shader.bindVertexAttribute(0, "vPosition");
	shader.bindVertexAttribute(1, "vColor");
	shader.link();
	shader.registerUniform("uWVP");

	float aspectRatio = window.getWidth() / (float)window.getHeight();
	glm::mat4 projection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
	glm::mat4 view       = glm::lookAt(
	    glm::vec3(4,3,3),
	    glm::vec3(0,0,0),
	    glm::vec3(0,1,0)
	);
	glm::mat4 world = glm::mat4(1.0f);
	glm::mat4 worldViewProjection = projection * view * world;


	while(!window.closed())
	{
		if(keyboard.wasKeyReleased(GLFW_KEY_ESCAPE))
			window.close();
		keyboard.update();

		window.prepare();

		// Render the current frame
		{
			GLVertexArray::bind(vao);
			GLBuffer::bind(ibo);
			shader.use();
			shader.getUniform("uWVP").set<glm::mat4>(worldViewProjection);
			glDrawElements(GL_TRIANGLES, ibo.getElementCount<uint16_t>(), GL_UNSIGNED_SHORT, nullptr);
			GLBuffer::unbind(ibo);
			GLVertexArray::unbind();
		}

		window.display();
	}

	return 0;
}
