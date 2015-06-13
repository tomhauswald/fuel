/*****************************************************************
 **' Main.cpp
 *****************************************************************
 **' Created on: 11.06.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "../graphics/GLWindow.h"
#include "../graphics/GLVertexArray.h"
#include "../graphics/GLFramebuffer.h"
#include "../input/Keyboard.h"

using namespace std;

int main(int argc, char **argv)
{
	fuel::graphics::GLWindow window({1280, 720, false, true});
	fuel::input::Keyboard keyboard(window);


	// Vertex array
	fuel::graphics::GLVertexArray vao(3);

	// Positions
	vao.getAttributeList(0).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT,
	{
		-1, 1, 0,
		 1, 1, 0,
		 1,-1, 0,
		-1,-1, 0,
	});

	// RGB colors
	vao.getAttributeList(1).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT,
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		1, 1, 0,
	});

	// Normals
	vao.getAttributeList(2).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT,
	{
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
	});


	// Index buffer
	fuel::graphics::GLBuffer ibo(GL_ELEMENT_ARRAY_BUFFER);
	ibo.write(GL_STATIC_DRAW, vector<uint16_t>
	{
		0, 3, 1,
		2, 3, 0
	});


	// Framebuffer
	fuel::graphics::GLFramebuffer fbo(window.getWidth(), window.getHeight());
	fbo.attach("depth", GL_DEPTH_COMPONENT32F);
	fbo.attach("diffuse", GL_RGB32F);
	fbo.attach("normal", GL_RGB32F);
	fbo.setDrawAttachments({"diffuse", "normal"});
	fuel::graphics::GLFramebuffer::bind(fbo);

	while(!window.closed())
	{
		if(keyboard.wasKeyReleased(GLFW_KEY_ESCAPE))
			window.close();

		keyboard.update();

		window.prepare();

		fuel::graphics::GLVertexArray::bind(vao);
		fuel::graphics::GLBuffer::bind(ibo);

		glDrawElements(GL_TRIANGLES, ibo.getElementCount<uint16_t>(), GL_UNSIGNED_SHORT, nullptr);
		window.display();

		fuel::graphics::GLBuffer::unbind(ibo);
		fuel::graphics::GLVertexArray::unbind();
	}

	fuel::graphics::GLFramebuffer::unbind();
	return 0;
}
