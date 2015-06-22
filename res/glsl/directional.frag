#version 400 core

//GBuffer textures
uniform sampler2D uDiffuseTexture;
uniform sampler2D uNormalTexture;

//Directional light characteristics
uniform vec3 uColor;
uniform vec3 uDirection;

//Input: Texture coordinates received from vertex shader
in vec2 fTexCoord;

//Output: Pixel color
out vec4 pColor;

float getIntensity()
{
	//Surface normal
	vec3 normal = normalize(texture(uNormalTexture, fTexCoord).xyz);
	return max(0.0f, dot(uDirection, -normal));
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