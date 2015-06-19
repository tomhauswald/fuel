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

float getIntensity()
{
	//Offset vector from light source
	vec3 offset = uPosition - texture(uPositionTexture, fTexCoord).xyz;

	//Distance from light
	float distance = length(offset);
	if(distance > uRadius) discard;

	//Surface normal
	vec3 normal = normalize(texture(uNormalTexture, fTexCoord).xyz);

	float i = 1.0f / (1.0f + distance * uLinearAttenuation + distance * distance * uQuadraticAttenuation);
	i *= dot(offset, normal);
	return max(i, 0.0f);
}

vec3 getColor()
{
	//Return product of diffuse and light color
	return uColor * texture(uDiffuseTexture, fTexCoord).rgb;
}

void main( void )
{	
	pColor = vec4(getIntensity() * getColor(), 1.0f);
}