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
#include "../graphics/GLTexture.h"
#include "../graphics/shaders/GLShaderProgram.h"
#include "../input/Keyboard.h"
#include "Transform.h"

#include <SOIL.h>

using namespace fuel;

shared_ptr<GLVertexArray> createColoredVertexArray(void)
{
	// Vertex array
	shared_ptr<GLVertexArray> pVAO = make_shared<GLVertexArray>(2);
	GLVertexArray::bind(*pVAO);

	// Positions
	pVAO->getAttributeList(0).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT,
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
	pVAO->getAttributeList(1).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT,
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

	return pVAO;
}

shared_ptr<GLVertexArray> createTexturedVertexArray(void)
{
	// Vertex array
	shared_ptr<GLVertexArray> pVAO = make_shared<GLVertexArray>(2);
	GLVertexArray::bind(*pVAO);

	// Positions
	pVAO->getAttributeList(0).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT,
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

	// Texture coordinates
	pVAO->getAttributeList(1).write<float, 2>(GL_STATIC_DRAW, GL_FLOAT,
	{
			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 1
	});
	GLVertexArray::unbind();

	return pVAO;
}

int main(int argc, char **argv)
{
	GLWindow window({1280, 720, false, true});
	Keyboard keyboard(window);

	auto pColoredVertexArray = createColoredVertexArray();
	auto pTexturedVertexArray = createTexturedVertexArray();

	// Index buffer
	GLBuffer ibo(GL_ELEMENT_ARRAY_BUFFER);
	ibo.write(GL_STATIC_DRAW, vector<uint16_t>
	{
		// Front face
		0, 1, 2, 2, 3, 0,

		// Right face
		4, 5, 6, 6, 7, 4,

		// Back face
		8, 9, 10, 10, 11, 8,

		// Left face
		12, 13, 14, 14, 15, 12,

		// Top Face
		16, 17, 18, 18, 19, 16,

		// Bottom Face
		20, 21, 22, 22, 23, 20
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


	GLShaderProgram coloredShader;
	coloredShader.setShader(EGLShaderType::VERTEX,   "res/glsl/colored.vert");
	coloredShader.setShader(EGLShaderType::FRAGMENT, "res/glsl/colored.frag");
	coloredShader.bindVertexAttribute(0, "vPosition");
	coloredShader.bindVertexAttribute(1, "vColor");
	coloredShader.link();
	coloredShader.registerUniform("uWVP");

	GLShaderProgram texturedShader;
	texturedShader.setShader(EGLShaderType::VERTEX,   "res/glsl/textured.vert");
	texturedShader.setShader(EGLShaderType::FRAGMENT, "res/glsl/textured.frag");
	texturedShader.bindVertexAttribute(0, "vPosition");
	texturedShader.bindVertexAttribute(1, "vTexCoord");
	texturedShader.link();
	texturedShader.registerUniform("uWVP");
	texturedShader.registerUniform("uTexture");

	float aspectRatio = window.getWidth() / (float)window.getHeight();
	glm::mat4 projection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
	glm::mat4 view       = glm::lookAt(
	    glm::vec3(0,0,5),
	    glm::vec3(0,0,0),
	    glm::vec3(0,1,0)
	);
	glm::mat4 viewProjection = projection * view;


	// Cube transforms
	Transform cubeTransforms[2];
	cubeTransforms[0].setPosition({-2.5f, 0, 0});
	cubeTransforms[1].setPosition({ 2.5f, 0, 0});

	// Cube texture
	GLTexture cubeTexture("res/textures/grass.png");

	while(!window.closed())
	{
		float time = static_cast<float>(glfwGetTime());
		if(keyboard.wasKeyReleased(GLFW_KEY_ESCAPE))
			window.close();
		keyboard.update();

		float freq = 90.0f;
		cubeTransforms[0].getRotation().y =  time * freq;
		cubeTransforms[1].getRotation().y = -time * freq;

		window.prepare();

		// Render the current frame
		{
			//-- Colored
			GLVertexArray::bind(*pColoredVertexArray);
			GLBuffer::bind(ibo);

			coloredShader.use();
			coloredShader.getUniform("uWVP").set(viewProjection * cubeTransforms[0].calculateWorldMatrix());
			glDrawElements(GL_TRIANGLES, ibo.getElementCount<uint16_t>(), GL_UNSIGNED_SHORT, nullptr);

			GLBuffer::unbind(ibo);
			GLVertexArray::unbind();



			//-- Textured
			GLVertexArray::bind(*pTexturedVertexArray);
			GLBuffer::bind(ibo);

			texturedShader.use();
			texturedShader.getUniform("uWVP").set(viewProjection * cubeTransforms[1].calculateWorldMatrix());
			texturedShader.getUniform("uTexture").set(cubeTexture.getID());
			glDrawElements(GL_TRIANGLES, ibo.getElementCount<uint16_t>(), GL_UNSIGNED_SHORT, nullptr);

			GLBuffer::unbind(ibo);
			GLVertexArray::unbind();
		}

		window.display();
	}

	return 0;
}
