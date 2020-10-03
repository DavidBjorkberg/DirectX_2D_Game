struct VS_IN
{
	float3 position : SV_POSITION;
	//float3 color : COLOR;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	//float3 color : COLOR;
};

VS_OUT main(VS_IN input)
{
	VS_OUT output;
	output.position = float4(input.position, 1);
	//output.color = input.color;
	return output;
}

