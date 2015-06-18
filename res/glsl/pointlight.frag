#version 400 core

//GBuffer textures
uniform sampler2D uDiffuseTexture;
uniform sampler2D uPositionTexture;
uniform sampler2D uNormalTexture;

//Point light characteristics
uniform vec3  uPosition;
uniform vec3  uColor;
uniform float uRadius;
uniform float uLinearAttenuation;
uniform float uQuadraticAttenuation;

//Input: Texture coordinates received from vertex shader
in vec2 fTexCoord;

//Output: Pixel color
out vec4 pColor;

float getIntensity(float distance)
{
	return 1.0f / (1.0f + distance * uLinearAttenuation + distance * distance * uQuadraticAttenuation);
}

void main( void )
{
	vec3  offset = uPosition - texture( uPositionTexture, fTexCoord ).xyz;
	float distance = length(offset);
	if(distance > uRadius) discard;

	float dot = dot( offset, normalize( texture( uNormalTexture, fTexCoord ).xyz) );

	//Sample the texture
	pColor = vec4( max(dot, 0.0f) * getIntensity(distance) * mix( uColor, texture( uDiffuseTexture, fTexCoord ).rgb, 0.5f ), 1.0f );
}