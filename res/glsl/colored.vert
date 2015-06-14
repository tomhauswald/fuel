#version 400 core

//Uniform: WorldViewProjection matrix
uniform mat4 uWVP;

//Input: Vertex position
in vec3 vPosition;

//Input: Vertex color
in vec3 vColor;

//Output: Vertex color
out vec4 fColor;

void main( void )
{
	gl_Position = uWVP * vec4(vPosition, 1.0f);
	fColor = vec4(vColor, 1.0f);
}