#version 400 core

//Uniform: WorldViewProjection matrix
uniform mat4 uWVP;

//Input: Vertex position
in vec3 vPosition;

//Input: Vertex texture coordinates
in vec2 vTexCoord;

//Output: Vertex color
out vec2 fTexCoord;

void main( void )
{
	//Transform position to screen space
	gl_Position = uWVP * vec4(vPosition, 1.0f);

	//Forward texture coordinates
	fTexCoord = vTexCoord; 
}