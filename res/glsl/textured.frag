#version 400 core

//Texture
uniform sampler2D uTexture;

//Texture coordinates received from vertex shader
in vec2 fTexCoord;

//Resulting pixel color
out vec4 pColor;

void main( void )
{
	//Sample the texture
	pColor = texture(uTexture, fTexCoord);
}