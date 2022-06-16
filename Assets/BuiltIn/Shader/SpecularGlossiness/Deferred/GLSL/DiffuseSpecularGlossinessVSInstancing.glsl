// File Generated by Assets/BuildShader.py - source: [DiffuseSpecularGlossinessVS.glsl : INSTANCING]
layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord0;
layout(location = 4) in vec4 uUVScale;
layout(location = 5) in vec4 uColor;
layout(location = 6) in vec4 uSpecGloss;
layout(location = 7) in mat4 uWorldMatrix;
uniform mat4 uVPMatrix;
uniform mat4 uView;
out vec3 vWorldNormal;
out vec4 vWorldPosition;
out vec2 vTexCoord0;
out vec4 vColor;
out vec4 vSpecGloss;
void main(void)
{
	vColor = uColor;
	vSpecGloss = uSpecGloss;
	mat4 uMvpMatrix = uVPMatrix * uWorldMatrix;
	vWorldPosition = uWorldMatrix * inPosition;
	vec4 sampleFragPos = uView * vWorldPosition;
	vWorldPosition.w = sampleFragPos.z;
	vec4 worldNormal = uWorldMatrix * vec4(inNormal, 0.0);
	vWorldNormal = normalize(worldNormal.xyz);
	vTexCoord0 = inTexCoord0 * uUVScale.xy + uUVScale.zw;
	gl_Position = uMvpMatrix * inPosition;
}
