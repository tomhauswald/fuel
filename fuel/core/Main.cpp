/*****************************************************************
 **' Main.cpp
 *****************************************************************
 **' Created on: 11.06.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "../graphics/GLWindow.h"
#include "../graphics/GLVertexArray.h"

using namespace std;

int main(int argc, char **argv)
{
	fuel::graphics::GLWindow window({1280, 720, false, true});

	fuel::graphics::GLVertexArray vao(3);
	vao.getAttributeList(0).write(GL_STATIC_DRAW, 3, GL_FLOAT, std::vector<float>
	{
		-1, 1, 0,
		 1, 1, 0,
		 1,-1, 0,
		-1,-1, 0,
	});
	vao.getAttributeList(1).write(GL_STATIC_DRAW, 3, GL_FLOAT, std::vector<float>
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		1, 1, 0,
	});
	vao.getAttributeList(2).write(GL_STATIC_DRAW, 3, GL_FLOAT, std::vector<float>
	{
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
	});

	cout << vao.getAttributeList(0).getBuffer().getElementCount<float>() << endl;
	cout << vao.getAttributeList(1).getBuffer().getElementCount<float>() << endl;
	cout << vao.getAttributeList(2).getBuffer().getElementCount<float>() << endl;

	while(!window.closed())
	{
		window.prepare();
		window.display();
	}

	return 0;
}
