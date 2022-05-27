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
VS_OUT main(VS_IN input)
{
	VS_OUT output;
	output.position = float4(input.position.x-1,input.position.y-1,1, 1);
	output.uv = input.uv;
	return output;
}