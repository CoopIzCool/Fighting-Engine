#pragma once

#include "DXCore.h"
#include <DirectXMath.h>
#include <wrl/client.h> // Used for ComPtr - a smart pointer for COM objects
#include "Mesh.h"
#include "Entity.h"
#include "Camera.h"
#include "Material.h"
#include "SimpleShader.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Sky.h"
#include "Enemy.h"
#include "Cannonball.h"
#include <vector>
#include <iostream>
#include <math.h>

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

private:

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateBasicGeometry();

	
	// Note the usage of ComPtr below
	//  - This is a smart pointer for objects that abide by the
	//    Component Object Model, which DirectX objects do
	//  - More info here: https://github.com/Microsoft/DirectXTK/wiki/ComPtr


	
	// Shaders and shader-related constructs
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelNormalShader;
	SimpleVertexShader* vertexNormalShader;
	SimplePixelShader* pixelSkyShader;
	SimpleVertexShader* vertexSkyShader;

	//meshes
	/*
	Mesh* meshWater;
	Mesh* meshCannon;
	Mesh* meshBoat;

	//entities
	Entity* water;
	Entity* playerBoat;
	Entity* entities[5];
	
	std::vector<Cannonball*> balls;
	std::vector<Enemy*> boats;
	//std::vector<Cannonball*> balls;
	//std::vector<Enemy*> boats;
	*/
	Camera* camera;
	/*
	Material* mWater;
	Material* mCannon;
	Material* mBoat;
	*/

	/*
	DirectionalLight light;
	DirectionalLight light2;
	DirectionalLight light3;
	DirectX::XMFLOAT3 ambient;
	DirectX::XMFLOAT3 ambient2;
	DirectX::XMFLOAT3 ambient3;

	PointLight pointLight;
	DirectX::XMFLOAT3 pointAmbient;

	//texture variables
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler; //one per program

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureSRVWater; //one per texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureSky;
	

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureCannon; //one per texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureCannonNorm;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureCannonRough;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureCannonMetal;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureBoat; //one per texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureBoatNorm;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureBoatRough;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureBoatMetal;
	Sky* sky;
	Mesh* meshSky;
	*/
	bool prevMouseClicked = false;
	int counter = 100;


	//bool gameOver = false;
	//int boatsShot = 0;
};

