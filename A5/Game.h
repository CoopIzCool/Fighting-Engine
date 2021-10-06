#pragma once

#include "DXCore.h"
#include <DirectXMath.h>
#include <wrl/client.h> // Used for ComPtr - a smart pointer for COM objects
#include "Mesh.h"
#include "Entity.h"
#include "Camera.h"
#include "Material.h"
#include "Player.h"
#include "Projectile.h"
#include <vector>
#include <iostream>
#include <stdlib.h>


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
	void PrintHealth();

private:

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateBasicGeometry();

	
	// Note the usage of ComPtr below
	//  - This is a smart pointer for objects that abide by the
	//    Component Object Model, which DirectX objects do
	//  - More info here: https://github.com/Microsoft/DirectXTK/wiki/ComPtr


	
	// Shaders and shader-related constructs
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

	//meshes
	Mesh* mesh1;
	Mesh* mesh2;
	Mesh* groundMesh;
	Mesh* projMesh;
	
	//shaders
	Microsoft::WRL::ComPtr<ID3D11Buffer> constBufferVS;

	//entities
	Entity* entity1;
	Entity* entity2;
	Entity* groundEntity;
	Entity* projEntity;
	
	//players
	Player* p1;
	Player* p2;
	Player* players[2];

	Camera* camera;
	//projectiles
	std::vector<Projectile*> projectiles;
	Material* m1;
	Material* m2;
	Material* groundMat;

	//player fired projectile states
	bool fired1 = false;
	bool fired2 = false;
};

