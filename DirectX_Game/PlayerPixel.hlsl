struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 uv : UV;
};
SamplerState _sampler : register(s0);
Texture2D colourTex : register(t0);

float4 main(VS_OUT input) : SV_TARGET
{
	float4 textureColor = colourTex.Sample(_sampler, input.uv);
	if (textureColor.x == 1 && textureColor.y == 1 && textureColor.z == 0)
	{
		clip(-1);
	}
	return textureColor;
}