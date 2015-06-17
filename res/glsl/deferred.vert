#version 400 core

//Uniform: WorldViewProjection matrix
uniform mat4 uWVP;

//Uniform: World matrix
uniform mat4 uWorld;

//Input: Vertex position
in vec3 vPosition;

//Input: Vertex normal
in vec3 vNormal;

//Input: Vertex texture coordinates
in vec2 vTexCoord;

//Output: World space position
out vec3 fPosition;

//Output: World space normal
out vec3 fNormal;

//Output: Texture coords
out vec2 fTexCoord;

void main( void )
{
	gl_Position = uWVP * vec4(vPosition, 1.0f);
	fPosition = (uWorld * vec4(vPosition, 1.0f)).xyz;
	fNormal = (uWorld * vec4(vNormal, 0.0f)).xyz;
	fTexCoord = vTexCoord;
}