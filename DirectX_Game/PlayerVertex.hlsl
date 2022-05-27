struct VS_IN
{
	float2 position : SV_POSITION;
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
cbuffer vsBuffer : register(b2)
{
	float4 FlippedXY;
};
cbuffer vsBuffer : register(b3)
{
	int currentFrame;
};

VS_OUT main(VS_IN input)
{
	VS_OUT output;
	float4x4 worldTrans = transpose(world);
	float4x4 viewProjTrans = transpose(viewProj);
	output.position = mul(float4(input.position, 1, 1), worldTrans);
	output.position = mul(output.position, viewProjTrans);

	float offsetX = 1.0f / 8.0f;
	if (FlippedXY.x == 0)
	{
		output.uv = float2(input.uv.x * offsetX, input.uv.y );
		output.uv += float2(offsetX * currentFrame, 0);
	}
	else
	{
		output.uv = float2(1 - input.uv.x * offsetX, input.uv.y );
		output.uv += float2(-offsetX * (7 - currentFrame), 0);
	}
	return output;
}

