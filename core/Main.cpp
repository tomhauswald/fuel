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

class TestGame : public Game
{
private:
	// Cube vertex array
	unique_ptr<GLVertexArray> m_pCubeVertexArray;

	// Cube index buffer
	unique_ptr<GLBuffer> m_pCubeIndexBuffer;

	// Point lights
	vector<PointLight> m_pointLights;

public:
	/**
	 * Load resources and setup scene.
	 */
	void setup(void) override
	{
		// Load textures
		getTextureManager().add("grass", "res/textures/grass.png");

		// Setup cube vertices
		m_pCubeVertexArray = make_unique<GLVertexArray>(3);
		GLVertexArray::bind(*m_pCubeVertexArray);
		m_pCubeVertexArray->getAttributeList(0).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT, CUBE_VERTICES);
		m_pCubeVertexArray->getAttributeList(1).write<float, 3>(GL_STATIC_DRAW, GL_FLOAT, CUBE_NORMALS);
		m_pCubeVertexArray->getAttributeList(2).write<float, 2>(GL_STATIC_DRAW, GL_FLOAT, CUBE_TEXTURE_COORDS);
		GLVertexArray::unbind();

		// Setup cube indices
		m_pCubeIndexBuffer = make_unique<GLBuffer>(GL_ELEMENT_ARRAY_BUFFER);
		GLBuffer::bind(*m_pCubeIndexBuffer);
		m_pCubeIndexBuffer->write(GL_STATIC_DRAW, CUBE_INDICES);
		GLBuffer::unbind(*m_pCubeIndexBuffer);
	}
};

int main(int argc, char **argv)
{
	TestGame g;
	g.run();
}

/*






	vector<PointLight> pointLights(3);
	pointLights[0].position = {-2.5f, 0, 1.5f};
	pointLights[0].color = {1, 0, 0};
	pointLights[0].setRadius(0.001f, 15);
	pointLights[1].position = {0, 0, -1.5f};
	pointLights[1].color = {0, 1, 0};
	pointLights[1].setRadius(0.001f, 15);
	pointLights[2].position = {2.5f, 0, 1.5f};
	pointLights[2].color = {0, 0, 1};
	pointLights[2].setRadius(0.001f, 15);

	// Fullscreen quad VAO
	GLVertexArray fullscreenQuadVertexArray(2);
	GLVertexArray::bind(fullscreenQuadVertexArray);
	fullscreenQuadVertexArray.getAttributeList(0).write<float, 2>(GL_STATIC_DRAW, GL_FLOAT,
	{
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
		-1.0f,  1.0f
	});
	fullscreenQuadVertexArray.getAttributeList(1).write<float, 2>(GL_STATIC_DRAW, GL_FLOAT,
	{
		 0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,
		 0.0f, 1.0f
	});
	GLVertexArray::unbind();

	// Calculate camera matrices
	float aspectRatio = window.getWidth() / (float)window.getHeight();
	glm::mat4 projection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
	glm::mat4 viewProjection = projection * camera.calculateViewMatrix();

	// Cube transforms
	Transform cubeTransforms[50];
	cubeTransforms[0].setPosition({-2.5f, 0, 0});
	cubeTransforms[1].setPosition({ 2.5f, 0, 0});

	// Load grass texture
	GLTexture grassTexture("res/textures/grass.png");

	while(!window.closed())
	{
		// Calculate passed time in seconds
		static float lastTime = static_cast<float>(glfwGetTime());
		float time 			  = static_cast<float>(glfwGetTime());
		float dt 			  = time - lastTime;
		lastTime 			  = time;

		if(keyboard.wasKeyReleased(GLFW_KEY_ESCAPE))
			window.close();
		keyboard.update();

		float freq = 90.0f;
		cubeTransforms[0].getRotation().y =  time * freq;
		cubeTransforms[0].getRotation().x =  time * (freq / sqrt(2));
		cubeTransforms[1].getRotation().y = -time * freq;
		cubeTransforms[1].getRotation().z =  time * (freq / sqrt(2));

		window.prepare();

		// Render the current frame
		{
			// Bind GBuffer
			GLFramebuffer::bind(deferredFramebuffer);
			GLFramebuffer::clear();
			prepareGeometryPass();
			deferredShader.use();
			{ // Geometry pass

				GLVertexArray::bind(cubeVertexArray);
				GLBuffer::bind(cubeIndexBuffer);
				GLTexture::bind(0, grassTexture); // Bind grass texture to unit 0

				// Draw first cube
				auto worldMatrix = cubeTransforms[0].calculateWorldMatrix();
				deferredShader.getUniform("uWorld").set(worldMatrix);
				deferredShader.getUniform("uWVP").set(viewProjection * worldMatrix);
				glDrawElements(GL_TRIANGLES, cubeIndexBuffer.getElementCount<uint16_t>(), GL_UNSIGNED_SHORT, nullptr);

				// Draw second cube
				worldMatrix = cubeTransforms[1].calculateWorldMatrix();
				deferredShader.getUniform("uWorld").set(worldMatrix);
				deferredShader.getUniform("uWVP").set(viewProjection * worldMatrix);
				glDrawElements(GL_TRIANGLES, cubeIndexBuffer.getElementCount<uint16_t>(), GL_UNSIGNED_SHORT, nullptr);

				GLTexture::unbind(0);
				GLBuffer::unbind(cubeIndexBuffer);
				GLVertexArray::unbind();
			}

			// Restore & clear default framebuffer
			GLFramebuffer::unbind();
			glClear(GL_COLOR_BUFFER_BIT);
			prepareLightPass();

			{ // Fullscreen passes

				GLVertexArray::bind(fullscreenQuadVertexArray);
				GLFramebuffer::bind(deferredFramebuffer, GLFramebuffer::READ);

				// Ambient pass
				ambientLightShader.use();
				glDrawArrays(GL_QUADS, 0, 4);

				// Directional light pass
				dirLightShader.use();
				glDrawArrays(GL_QUADS, 0, 4);

				// Point light passes
				pointLightShader.use();
				pointLightShader.getUniform("uViewProjection").set(projection * camera.calculateViewMatrix());
				pointLightShader.getUniform("uCameraPosition").set(camera.getTransform().getPosition());
				for(unsigned light=0; light<pointLights.size(); light++)
				{
					pointLightShader.getUniform("uPosition").set(pointLights[light].position);
					pointLightShader.getUniform("uColor").set(pointLights[light].color);
					pointLightShader.getUniform("uRadius").set(pointLights[light].getRadius());
					pointLightShader.getUniform("uLinearAttenuation").set(pointLights[light].linearAttenuation);
					pointLightShader.getUniform("uQuadraticAttenuation").set(pointLights[light].quadraticAttenuation);
					glDrawArrays(GL_QUADS, 0, 4);
				}

				GLTexture::unbind({0, 1, 2});
				GLVertexArray::unbind();
			}

			glUseProgram(GL_NONE);
			prepareGeometryPass();
			// Render downsampled gbuffer textures as overlay
			static constexpr uint16_t previewWidth = 160, previewHeight = 90;
			deferredFramebuffer.showAttachmentContent("diffuse",    		 0, previewHeight, previewWidth, previewHeight);
			deferredFramebuffer.showAttachmentContent("position",   		 0, 		    0, previewWidth, previewHeight);
			deferredFramebuffer.showAttachmentContent("depth",   previewWidth,  		    0, previewWidth, previewHeight);
		}

		window.display();

		// Busy waiting :(
		while((time = static_cast<float>(glfwGetTime())) - lastTime < 1.0f / 60);
	}

	return 0;
}

*/
