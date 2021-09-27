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
//Texture2D textureSRV	  : register(t0);
//Texture2D normalTextureSRV	  : register(t1);
//

Texture2D Albedo:  register(t0);
Texture2D NormalMap:  register(t1);
Texture2D RoughnessMap   :  register(t2);
Texture2D MetalnessMap   :  register(t3);
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
float4 main(VertexToPixelNormalMap input) : SV_TARGET
{
	float4 textureColor = pow((Albedo.Sample(basicSampler, input.uv)), 2.2f);
	
	//unpack the normal map
	float3 unpackedNormal = NormalMap.Sample(basicSampler, input.uv).rgb * 2 - 1;

	//get roughness and metalness

	float roughness = RoughnessMap.Sample(basicSampler, input.uv).r;
	float metalness = MetalnessMap.Sample(basicSampler, input.uv).r;

	//get specularcolor
	float3 specularColor = lerp(F0_NON_METAL.rrr, textureColor.rgb, metalness);

	input.normal = normalize(input.normal);
	input.tangent = normalize(input.tangent);

	float3 N = input.normal;  // Must be normalized
	float3 T = input.tangent; // Must be normalized
	T = normalize(T - N * dot(T, N)); // Gram-Schmidt orthogonalization 
	float3 B = cross(T, N); 
	float3x3 TBN = float3x3(T, B, N);
	input.normal = normalize(mul(unpackedNormal, TBN));

	
	float3 surfaceColor = input.color.rgb * textureColor.rgb;

	//direction of the camera 
	float3 cameraDir = normalize(cameraPos - input.worldPos);

	//return input.normal.xyzz;
	
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
		float3 spec = MicrofacetBRDF(input.normal, lightDirNorm, cameraDir, roughness, metalness, specularColor);
		float3 spec2 = MicrofacetBRDF(input.normal, lightDirNorm2, cameraDir, roughness, metalness, specularColor);
		float3 spec3 = MicrofacetBRDF(input.normal, lightDirNorm3, cameraDir, roughness, metalness, specularColor);

		//balanced 
		float3 balancedDiff = DiffuseEnergyConserve(diffusedLight, spec, metalness);
		float3 balancedDiff2 = DiffuseEnergyConserve(diffusedLight2, spec2, metalness);
		float3 balancedDiff3 = DiffuseEnergyConserve(diffusedLight3, spec3, metalness);

		//light combination
		float3 finalLight =
			((balancedDiff * surfaceColor + spec) * light.intensity * light.color) +
			((balancedDiff2 * surfaceColor + spec2) * light2.intensity * light2.color) +
			((balancedDiff3 * surfaceColor + spec3) * light3.intensity * light3.color);
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
		float3 spec = MicrofacetBRDF(input.normal, lightDirNorm, cameraDir, roughness, metalness, specularColor);
		float3 spec2 = MicrofacetBRDF(input.normal, lightDirNorm2, cameraDir, roughness, metalness, specularColor);
		float3 spec3 = MicrofacetBRDF(input.normal, lightDirNorm3, cameraDir, roughness, metalness, specularColor);

		//get diffused spotlight
		float3 pointLightDirNorm = normalize(input.worldPos - pointLight.position);
		float diffusedPointLight = Diffuse(input.normal, -pointLightDirNorm);
		float3 specPoint = MicrofacetBRDF(input.normal, pointLightDirNorm, cameraDir, roughness, metalness, specularColor);

		//calculatebalancedlightdifference
		float3 balancedDiff = DiffuseEnergyConserve(diffusedLight, spec, metalness);
		float3 balancedDiff2 = DiffuseEnergyConserve(diffusedLight2, spec2, metalness);
		float3 balancedDiff3 = DiffuseEnergyConserve(diffusedLight3, spec3, metalness);
		float3 balancedDiffPoint = DiffuseEnergyConserve(diffusedPointLight, specPoint, metalness);

		//final light
		float3 finalLight =
			((balancedDiff * surfaceColor + spec) * light.intensity * light.color) +
			((balancedDiff2 * surfaceColor + spec2) * light2.intensity * light2.color) +
			((balancedDiff3 * surfaceColor + spec3) * light3.intensity * light3.color) +
			((balancedDiffPoint * surfaceColor + specPoint) * pointLight.intensity * pointLight.color);

		return float4(pow(finalLight, 1.0f / 2.2f), 1);
	}
	else
	{
		return float4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	

}