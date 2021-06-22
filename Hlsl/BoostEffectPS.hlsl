#include "Particle.hlsli"


Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 motionBlur(float2 uv)
{
	float power = 0.1f;

	float4 output = 0;
	for (int i = 0; i < 9; i++)
	{
		output += tex.Sample(samLinear, uv
			+ float2(sin(Time.x - i*0.1f)*0.05f, 0.0f)) * power*(10.0f - i) / 5.0f;
	}

	return output;
}

float random(float2 uv)
{
	return frac(sin(dot(uv, float2(12.9898f, 78.233f)))* 43758.5453f);
}
float perlinNoise(float2 uv) {
	float2 p = floor(uv);
	float2 f = frac(uv);
	float2 u = f * f * (3.0f - 2.0f * f);
	float v00 = random(p + float2(0, 0));
	float v10 = random(p + float2(1, 0));
	float v01 = random(p + float2(0, 1));
	float v11 = random(p + float2(1, 1));

	return lerp(
		lerp(dot(v00, f - float2(0, 0)), dot(v10, f - float2(1, 0)), u.x),
		lerp(dot(v01, f - float2(0, 1)), dot(v11, f - float2(1, 1)), u.x),
		u.y) + 0.5f;
}
float4 main(PS_INPUT input) : SV_TARGET
{
	//float4 ret = tex.Sample(samLinear, input.Tex);
	//return ret;


	float2 uv = input.Tex;
	float w = 5.0f;
	float h = 1.0f;
	uv.x /= w;
	uv.y /= h;
	float time = floor(Time.x * 60.0f);

	uv.x += (1.0f / w) * (time % w);

	return tex.Sample(samLinear,uv);
}