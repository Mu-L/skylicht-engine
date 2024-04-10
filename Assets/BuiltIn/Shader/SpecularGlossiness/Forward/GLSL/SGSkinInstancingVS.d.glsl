layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec4 inColor;
layout(location = 3) in vec2 inTexCoord0;
layout(location = 4) in vec3 inTangent;
layout(location = 5) in vec3 inBinormal;
layout(location = 6) in vec2 inData;
layout(location = 7) in vec4 inBlendIndex;
layout(location = 8) in vec4 inBlendWeight;

layout(location = 9) in vec4 uUVScale;
layout(location = 10) in vec4 uColor;
layout(location = 11) in vec2 uSpecGloss;

layout(location = 12) in mat4 uWorldMatrix;

uniform sampler2D uTransformTexture;

uniform mat4 uMvpMatrix;
uniform vec4 uCameraPosition;
uniform vec4 uLightDirection;
uniform vec4 uUVScale;
uniform vec2 uTransformTextureSize;

out vec2 vTexCoord0;
out vec3 vWorldNormal;
out vec3 vWorldViewDir;
out vec3 vWorldLightDir;
out vec3 vWorldTangent;
out vec3 vWorldBinormal;
out float vTangentW;
out vec4 vViewPosition;
out vec3 vWorldPosition;

#include "../../../TransformTexture/GLSL/LibTransformTexture.glsl"

void main(void)
{
	mat4 skinMatrix = mat4(0.0);
	vec4 skinPosition = vec4(0.0);
	vec3 skinNormal = vec3(0.0);
	vec3 skinTangent = vec3(0.0);

	vec2 boneLocation = vec2(0.0);

	boneLocation.y = inBlendIndex[0];
	skinMatrix = inBlendWeight[0] * getTransformFromTexture(boneLocation);

	boneLocation.y = inBlendIndex[1];
	skinMatrix += inBlendWeight[1] * getTransformFromTexture(boneLocation);

	boneLocation.y = inBlendIndex[2];
	skinMatrix += inBlendWeight[2] * getTransformFromTexture(boneLocation);

	boneLocation.y = inBlendIndex[3];
	skinMatrix += inBlendWeight[3] * getTransformFromTexture(boneLocation);

	skinPosition = skinMatrix * inPosition;
	skinNormal = (skinMatrix * vec4(inNormal, 0.0)).xyz;
	skinTangent = (skinMatrix * vec4(inTangent, 0.0)).xyz;

	vTexCoord0 = inTexCoord0 * uUVScale.xy + uUVScale.zw;
	vTangentW = inData.x;

	vec4 worldPos = uWorldMatrix * skinPosition;
	vec4 worldViewDir = normalize(uCameraPosition - worldPos);

	vec4 worldNormal = uWorldMatrix * vec4(skinNormal.xyz, 0.0);
	vec4 worldTangent = uWorldMatrix * vec4(skinTangent.xyz, 0.0);

	vWorldPosition = worldPos.xyz;

	vWorldNormal = normalize(worldNormal.xyz);
	vWorldTangent = normalize(worldTangent.xyz);
	vWorldBinormal = normalize(cross(worldNormal.xyz, worldTangent.xyz));

	vWorldViewDir = worldViewDir.xyz;
	vWorldLightDir = normalize(uLightDirection.xyz);
	vViewPosition = uMvpMatrix * skinPosition;

	gl_Position = vViewPosition;
}