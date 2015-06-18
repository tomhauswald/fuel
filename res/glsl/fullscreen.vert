#version 400 core

//Input: Vertex position
layout(location = 0) in vec2 vPosition;

//Input: Vertex texture coordinates
layout(location = 1) in vec2 vTexCoord;

//Output: Vertex color
out vec2 fTexCoord;

void main( void )
{
	gl_Position = vec4(vPosition, 0.0f, 1.0f);
	fTexCoord = vTexCoord;
}