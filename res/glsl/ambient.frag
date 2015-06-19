#version 400 core

//GBuffer textures
uniform sampler2D uDiffuseTexture;
uniform sampler2D uPositionTexture;
uniform sampler2D uNormalTexture;

//Ambient light characteristics
uniform vec3  uColor;
uniform float uIntensity;

//Input: Texture coordinates received from vertex shader
in vec2 fTexCoord;

//Output: Pixel color
out vec4 pColor;

vec3 getColor()
{
	//Return product of diffuse and light color
	return uColor * texture(uDiffuseTexture, fTexCoord).rgb;
}

void main( void )
{	
	pColor = vec4(uIntensity * getColor(), 1.0f);
}