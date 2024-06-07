// File Generated by Assets/BuildShader.py - source: [TextureSRGBFS.d.hlsl : _]
Texture2D uTexDiffuse : register(t0);
SamplerState uTexDiffuseSampler : register(s0);
struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
	float2 tex0 : TEXCOORD0;
};
cbuffer cbPerFrame
{
	float4 uColor;
	float2 uIntensity;
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
float4 main(PS_INPUT input) : SV_TARGET
{
	float4 result = input.color * uTexDiffuse.SampleLevel(uTexDiffuseSampler, input.tex0, 0) * uColor;
	return float4(sRGB(result.rgb * uIntensity.x), result.a);
}
