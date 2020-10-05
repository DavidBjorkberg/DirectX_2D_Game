
struct VS_OUT
{
	float4 position : SV_POSITION;
	//	float3 color : COLOR;
};

float4 main(VS_OUT input) : SV_TARGET
{
	return float4(0,1,0,1);
}