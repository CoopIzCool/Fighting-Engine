#include "Includes.hlsli"

cbuffer ExternalData : register(b0)
{
	matrix view;
	matrix projection;
}

VertexToPixelSkyBox main( VertexShaderInput input )
{
	VertexToPixelSkyBox output;
	matrix viewCopy = view;
	viewCopy._14 = 0;
	viewCopy._24 = 0;
	viewCopy._34 = 0;

	matrix vp = mul(projection, viewCopy);

	output.position = mul(vp, float4(input.position, 1.0f));
	output.position.z = output.position.w;

	output.sampleDir = input.position;

	return output;
}