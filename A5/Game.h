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
#include <string>
#include "Inputs.h"
#include "HitBoxType.h"
#include "InputRegister.h"


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
	void PlayerHit(bool isP1);
	bool facingRight();

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

	//down tilts
	Mesh* dTiltMeshes[5];
	Entity* dTiltEntities[5];

	//forward tilt
	Mesh* fTiltMeshes[5];
	Entity* fTiltEntities[5];

	Mesh* nullMeshes[5];
	Entity* nullEntities[5];

	//projectiles
	std::vector<Projectile*> projectiles;
	std::queue<Projectile*> projQueue;
	
	//jabs
	std::queue<Hitbox*> jabQueue;
	//down tilts
	std::queue<Hitbox*> dTiltQueue;
	//forward tilts
	std::queue<Hitbox*> fTiltQueue;
	//null hitboxes
	std::queue<Hitbox*> nullQueue;

	//entities for hitbars

	Mesh* healthBarMesh1;
	Material* healthBarMaterial1;
	Entity* healthBarEntity1;

	Mesh* healthBarMesh2;
	Material* healthBarMaterial2;
	Entity* healthBarEntity2;

	Entity* healthBars[2];
	//player attack states
	bool p1Starting = false;
	bool p2Starting = false;
	bool p1Active = false;
	bool p2Active = false;
	bool p1End = false;
	bool p2End = false;
	bool p1Hit = false;
	bool p2Hit = false;
	float p1Frames;
	float p2Frames;


	//input logs
	std::vector<InputRegister*> InputLog1;
	std::vector<InputRegister*> InputLog2;
	std::queue<InputRegister*> inputQueue;

	//bool stats because there is no on key pressed function
	bool p1Up = false;
	bool p1Down = false;
	bool p1Left = false;
	bool p1Right = false;
	bool p2Up = false;
	bool p2Down = false;
	bool p2Left = false;
	bool p2Right = false;
	 
};

