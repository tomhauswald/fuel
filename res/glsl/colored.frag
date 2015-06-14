#version 400 core

//Color value received from vertex shader
in vec4 fColor;

//Resulting pixel color
out vec4 pColor;

void main( void )
{
	//Use received fragment color
	pColor = fColor;
}