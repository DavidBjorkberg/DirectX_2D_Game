struct VS_IN
{
	float3 position : SV_POSITION;
	float2 uv : UV;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	//float3 color : COLOR;
};
cbuffer vsBuffer : register(b0)
{
	float4x4 viewProj;
};
VS_OUT main(VS_IN input)
{
	VS_OUT output;
	float4x4 viewProjTrans = transpose(viewProj);
	output.position = mul(float4(input.position, 1), viewProjTrans);
	//output.color = input.color;
	return output;
}

