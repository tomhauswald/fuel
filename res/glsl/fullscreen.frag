#version 400 core

//GBuffer textures
uniform sampler2D uDiffuseTexture;
uniform sampler2D uPositionTexture;
uniform sampler2D uNormalTexture;

//Input: Texture coordinates received from vertex shader
in vec2 fTexCoord;

//Output: Pixel color
out vec4 pColor;

void main( void )
{
	//Sample the texture
	pColor = mix( vec4( 0.0f, 0.0f, 1.0f, 1.0f ), texture( uDiffuseTexture, fTexCoord ), 0.9f );
}