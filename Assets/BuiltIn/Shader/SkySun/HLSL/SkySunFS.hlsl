// File Generated by Assets/BuildShader.py - source: [SkySunFS.d.hlsl : _]
struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
	float2 tex0 : TEXCOORD0;
	float4 worldPos: WORLD_POSITION;
};
cbuffer cbPerFrame
{
	float4 uLightDirection;
	float4 uCamPosition;
	float4 uIntensity;
	float4 uAtmospheric;
	float4 uSun;
	float4 uGlare1;
	float4 uGlare2;
};
static const float gamma = 2.2;
static const float invGamma = 1.0 / 2.2;
float3 sRGB(float3 color)
{
	return pow(color, gamma);
}
float3 linearRGB(float3 color)
{
	return pow(color, invGamma);
}
float3 GetSkyColor(
	float3 viewDir,
	float3 sunDirection,
	float intensity,
	float4 atmosphericColor,
	float4 sunColor,
	float4 glowColor1,
	float4 glowColor2,
	float sunRadius)
{
	float y = 1.0 - (max(viewDir.y, 0.0) * 0.8 + 0.2) * 0.8;
	float3 skyColor = float3(pow(y, 2.0), y, 0.6 + y*0.4) * intensity;
	float sunAmount = max(dot(sunDirection, viewDir), 0.0);
	skyColor += atmosphericColor.rgb * sunAmount * sunAmount * atmosphericColor.a;
	skyColor += sunColor.rgb * pow(sunAmount, sunRadius) * sunColor.a;
	skyColor += glowColor1.rgb * pow(sunAmount, 8.0) * glowColor1.a;
	skyColor += glowColor2.rgb * pow(sunAmount, 3.0) * glowColor2.a;
	return skyColor;
}
float4 main(PS_INPUT input) : SV_TARGET
{
	float3 viewDir = normalize(input.worldPos.xyz - uCamPosition.xyz);
	float y = 1.0 - (max(viewDir.y, 0.0) * 0.8 + 0.2) * 0.8;
	float3 skyColor = GetSkyColor(
		viewDir,
		uLightDirection.xyz,
		uIntensity.x,
		uAtmospheric,
		uSun,
		uGlare1,
		uGlare2,
		uIntensity.y
	);
	float3 groundColor = float3(0.4, 0.4, 0.4);
	float3 result = lerp(skyColor, sRGB(groundColor), pow(smoothstep(0.0,-0.025, viewDir.y), 0.2));
	return float4(result, 1.0);
}
