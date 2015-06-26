/*****************************************************************
 **' Main.cpp
 *****************************************************************
 **' Created on: 11.06.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "Game.h"
#include "../graphics/lighting/PointLight.h"

#define RESOLUTION_X		 	1600
#define RESOLUTION_Y 			900
#define AMBIENT_PASS			1
#define DIRECTIONAL_PASS		1
#define POINT_PASS				1
#define SHOW_GBUFFER_TEXTURES	1

using namespace fuel;

class Cube : public GameComponent
{
private:
	string m_textureName;
	GLVertexArray m_vertices;
	GLBuffer m_indices;
	Transform m_transform;

public:
	Cube(void)
		:m_textureName("grass"),
		 m_vertices(3),
		 m_indices(GL_ELEMENT_ARRAY_BUFFER),
		 m_transform()
	{
		GLVertexArray::bind(m_vertices);
		m_vertices.getAttributeList(0).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT, CUBE_VERTICES);
		m_vertices.getAttributeList(1).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT, CUBE_NORMALS);
		m_vertices.getAttributeList(2).write<float, 2>(GL_STATIC_DRAW, GL_FLOAT, CUBE_TEXTURE_COORDS);

		m_indices.write(GL_STATIC_DRAW, CUBE_INDICES);
	}

	void setPosition(const glm::vec3 &position)
	{
		m_transform.setPosition(position);
	}

	void update(Game &game, float dt) override
	{
		m_transform.getRotation().y += dt * 90.0f;
	}

	void render(Game &game) override
	{
		GLShaderProgram &shader = game.getShaderManager().get("textured");
		shader.use();
		shader.getUniform("uWorld").set(m_transform.calculateWorldMatrix());
		shader.getUniform("uWVP").set(game.calculateViewProjectionMatrix() * m_transform.calculateWorldMatrix());
		GLTexture::bind(0, game.getTextureManager().get(m_textureName));
		game.getWindow().renderGeometry<uint16_t>(m_vertices, m_indices, GL_UNSIGNED_SHORT);
	}
};

class EngineTest : public Game, public GameComponent
{
private:
	shared_ptr<Cube> m_pCubes[2];

public:
	/**
	 * Load resources and setup scene.
	 */
	void setup(void) override
	{
		// Load textures
		getTextureManager().add("grass", "res/textures/grass.png");

		// Setup cubes
		m_pCubes[0] = make_shared<Cube>();
		m_pCubes[0]->setPosition({-2.5f, 0.0f, 0.0f});
		m_pCubes[1] = make_shared<Cube>();
		m_pCubes[1]->setPosition({+2.5f, 0.0f, 0.0f});

		// Start scene
		setSceneRoot(this);
		addChild("cubes[0]", m_pCubes[0]);
		addChild("cubes[1]", m_pCubes[1]);
	}
};

int main(int argc, char **argv)
{
	EngineTest test;
	test.run();
}
