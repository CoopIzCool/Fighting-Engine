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
#include <queue>


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
	
	//shaders
	Microsoft::WRL::ComPtr<ID3D11Buffer> constBufferVS;

	//entities
	Entity* entity1;
	Entity* entity2;
	Entity* groundEntity;
	
	//players
	Player* p1;
	Player* p2;
	Player* players[2];
	
	//camera
	Camera* camera;

	//materials
	Material* m1;
	Material* m2;
	Material* groundMat;
	Material* transparentMat;

	//player attack states
	bool fired1 = false;
	bool fired2 = false;
	bool attacked1 = false;
	bool attacked2 = false;

	//hitbox storages for mesh/entity
	
	//projectiles
	Mesh* projMeshes[10];
	Entity* projEntities[10];

	//jabs
	Mesh* jabMeshes[5];
	Entity* jabEntities[5];

	//projectiles
	std::vector<Projectile*> projectiles;
	std::queue<Projectile*> projQueue;

	//player attack states
	bool p1Starting = false;
	bool p2Starting = false;
	bool p1Active = false;
	bool p2Active = false;
	bool p1End = false;
	bool p2End = false;


	float p1Frames;
	float p2Frames;

	Microsoft::WRL::ComPtr<ID3D10Texture2D> texture;
	//h ttps://docs.microsoft.com/en-us/windows/win32/direct3d10/d3d10-graphics-programming-guide-resources-creating-textures#create-a-texture-from-a-file
};

