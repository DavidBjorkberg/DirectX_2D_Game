struct VS_IN
{
	float3 position : SV_POSITION;
	float2 uv : UV;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 uv : UV;
};
cbuffer vsBuffer : register(b0)
{
	float4x4 viewProj;
};
cbuffer vsBuffer : register(b1)
{
	float4x4 world;
};
VS_OUT main(VS_IN input)
{
	VS_OUT output;
	//float4x4 wvp = mul(world, viewProj);
	//float4x4 wvpTrans = transpose(wvp);
	float4x4 worldTrans = transpose(world);
	float4x4 viewProjTrans = transpose(viewProj);
	output.position = mul(float4(input.position, 1), worldTrans);
	output.position = mul(output.position, viewProjTrans);
	output.uv = input.uv;
	//output.color = input.color;
	return output;
}

