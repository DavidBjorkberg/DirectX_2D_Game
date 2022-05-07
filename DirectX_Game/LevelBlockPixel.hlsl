
struct VS_OUT
{
	float4 position : SV_POSITION;
	float4 uv : UV;
};

SamplerState _sampler : register(s0);
Texture2D colourTex : register(t0);
float4 main(VS_OUT input) : SV_TARGET
{
	float2 sampleUV;
	
	float3 textureColor = colourTex.Sample(_sampler, input.uv.xy).rgb;
	if (textureColor.x == 0 && textureColor.y == 0 && textureColor.z == 0)
	{
		clip(-1);
	}
	return float4(textureColor,1);
}