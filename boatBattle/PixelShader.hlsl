#include "Includes.hlsli"

cbuffer ExternalData : register(b0)
{
	DirectionalLight light;
	float3 ambientColor;
	DirectionalLight light2;
	float3 ambientColor2;
	DirectionalLight light3;
	float3 ambientColor3;
	PointLight pointLight;
	float3 pointAmbient;
	int lightType;
	float3 cameraPos;
	float matShine;

}

//define textures
Texture2D textureSRV	  : register(t0);
SamplerState basicSampler : register(s0);


// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	float3 textureColor = pow(textureSRV.Sample(basicSampler,input.uv).rgb,2.2f);
	

	input.normal = normalize(input.normal);

	float3 surfaceColor = input.color.rgb * textureColor;

	//direction of the camera 
	float3 cameraDir = normalize(cameraPos - input.worldPos);
	
	if (lightType == 0)
	{

		//get normaized light directions
		float3 lightDirNorm = normalize(light.direction);
		float3 lightDirNorm2 = normalize(light2.direction);
		float3 lightDirNorm3 = normalize(light3.direction);
		//get diffused light
		float diffusedLight = Diffuse(input.normal, -lightDirNorm);
		float diffusedLight2 = Diffuse(input.normal, -lightDirNorm2);
		float diffusedLight3 = Diffuse(input.normal, -lightDirNorm3);
		//get specular light
		float spec = SpecularPhong(input.normal, lightDirNorm, cameraDir, matShine);
		float spec2 = SpecularPhong(input.normal, lightDirNorm2, cameraDir, matShine);
		float spec3 = SpecularPhong(input.normal, lightDirNorm3, cameraDir, matShine);
		//light combination
		float3 finalLight =
		(surfaceColor * ambientColor +
			(diffusedLight * light.color * surfaceColor) + (spec.rrr)) +
		(surfaceColor * ambientColor +
			(diffusedLight2 * light.color * surfaceColor) + (spec2.rrr)) +
		(surfaceColor * ambientColor +
			(diffusedLight3 * light.color * surfaceColor) + (spec3.rrr));
		return float4(pow(finalLight, 1.0f / 2.2f), 1);
	}

	else if (lightType == 1)
	{
		//get normaized light directions
		float3 lightDirNorm = normalize(light.direction);
		float3 lightDirNorm2 = normalize(light2.direction);
		float3 lightDirNorm3 = normalize(light3.direction);
		//get diffused light
		float diffusedLight = Diffuse(input.normal, -lightDirNorm);
		float diffusedLight2 = Diffuse(input.normal, -lightDirNorm2);
		float diffusedLight3 = Diffuse(input.normal, -lightDirNorm3);
		//get specular light
		float spec = SpecularPhong(input.normal, lightDirNorm, cameraDir, matShine);
		float spec2 = SpecularPhong(input.normal, lightDirNorm2, cameraDir, matShine);
		float spec3 = SpecularPhong(input.normal, lightDirNorm3, cameraDir, matShine);
		//get diffused spotlight
		float3 pointLightDirNorm = normalize(input.worldPos - pointLight.position);
		float diffusedPointLight = Diffuse(input.normal, -pointLightDirNorm);
		float specPoint = SpecularPhong(input.normal, pointLightDirNorm, cameraDir, matShine);
		//light combination
		float3 finalLight =
		(surfaceColor * ambientColor +
			(diffusedLight * light.color * surfaceColor) + (spec.rrr)) +
		(surfaceColor * ambientColor +
			(diffusedLight2 * light.color * surfaceColor) + (spec2.rrr)) +
		(surfaceColor * ambientColor +
			(diffusedLight3 * light.color * surfaceColor) + (spec3.rrr)) +
		(surfaceColor * ambientColor +
			(diffusedPointLight * light.color * surfaceColor) + (specPoint.rrr));
		return float4(pow(finalLight,1.0f/2.2f), 1);
	}
	else
	{
		return float4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	

}