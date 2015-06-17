#version 400 core

//Uniform: Texture to use
uniform sampler2D uDiffuseTexture;

//Input: World space position
in vec3 fPosition;

//Input: World space normal
in vec3 fNormal;

//Input: Texture coords
in vec2 fTexCoord;

//Output: GBuffer diffuse
out vec3 pDiffuse;

//Output: GBuffer position
out vec3 pPosition;

//Output: GBuffer normal
out vec3 pNormal;

//Output: GBuffer texture coordinate
out vec3 pTexCoord;

void main( void )
{
	pDiffuse = texture(uDiffuseTexture, fTexCoord).rgb;
	pPosition = fPosition;
	pNormal = normalize(fNormal);
	pTexCoord = vec3(fTexCoord, 0);
}