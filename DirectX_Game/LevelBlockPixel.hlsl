
struct VS_OUT
{
	float4 position : SV_POSITION;
//	float3 color : COLOR;
};

float4 main(VS_OUT input) : SV_TARGET
{
	return float4(1,0,0,1);
}