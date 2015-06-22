#version 400 core

//Billboard effect
const float cBillboardRadius = 0.0625f;
const float cAspectRatio = 16.0f / 9.0f;
const float cCameraMaxDistance = 16.0f;

//ViewProjection matrix
uniform mat4 uViewProjection;

//Camera position in world space
uniform vec3 uCameraPosition;

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

float getIntensity( void )
{
	//Offset vector from light source
	vec3 offset = uPosition - texture(uPositionTexture, fTexCoord).xyz;

	//Distance from light to camera
	float distance = length(offset);
	if(distance > uRadius) discard;

	//Surface normal
	vec3 normal = normalize(texture(uNormalTexture, fTexCoord).xyz);

	float i = 1.0f / (1.0f + distance * uLinearAttenuation + distance * distance * uQuadraticAttenuation);
	i *= dot(offset, normal);
	return max(i, 0.0f);
}

vec3 getColor( void )
{
	
	//Return product of diffuse and light color
	return uColor * texture(uDiffuseTexture, fTexCoord).rgb;
}

void main( void )
{
	vec4  clipSpaceLightPos   = (uViewProjection * vec4(uPosition, 1.0f));
	vec3  screenSpaceLightPos = clipSpaceLightPos.xyz / clipSpaceLightPos.w;
		 screenSpaceLightPos.y /= cAspectRatio;
	vec2  screenSpaceTexCoord = 2.0f * fTexCoord - 1.0f;
		 screenSpaceTexCoord.y /= cAspectRatio;
	float screenSpaceDistance = length(screenSpaceLightPos.xy - screenSpaceTexCoord);
	
	float cameraDistance     = length(uCameraPosition - uPosition);
	float adaptedBillboardSz = cBillboardRadius * (1.0f - cameraDistance / cCameraMaxDistance);
	
	pColor = vec4(getIntensity() * getColor(), 1.0f);
	if(screenSpaceDistance <= adaptedBillboardSz )
		pColor += vec4(uColor * (1.0f - screenSpaceDistance / adaptedBillboardSz ), 1.0f);
}