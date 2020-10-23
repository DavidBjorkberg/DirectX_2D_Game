struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 uv : UV;
};
SamplerState _sampler;
Texture2D fullHeartsTex : register(t0);
Texture2D emptyHeartsTex : register(t1);
cbuffer psBuffer : register(b0)
{
	float healthPercent;
};
float4 main(VS_OUT input) : SV_TARGET
{
	float4 textureColor;
	if (input.uv.x > healthPercent)
	{
		textureColor = emptyHeartsTex.Sample(_sampler, input.uv);
	}
	else
	{
		textureColor = fullHeartsTex.Sample(_sampler, input.uv);
	}
	if (textureColor.x == 1 && textureColor.y == 1 && textureColor.z == 0)
	{
		clip(-1);
	}
	return float4(textureColor);
}