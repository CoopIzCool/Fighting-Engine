#include "Game.h"
#include "Vertex.h"
#include "BufferStruct.h"

// Needed for a helper function to read compiled shader files from the hard drive
#pragma comment(lib, "d3dcompiler.lib")
#include <d3dcompiler.h>

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.\n");
#endif

	//new camera
	camera = new Camera(0, 0.5, -2, (float)width / height);


}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Note: Since we're using smart pointers (ComPtr),
	// we don't need to explicitly clean up those DirectX objects
	// - If we weren't using smart pointers, we'd need
	//   to call Release() on each DirectX object created in Game
	delete(mesh1);
	delete(mesh2);
	delete(groundMesh);

	if (p1->HasHitBox())
	{
		delete(p1->UsedHitbox());
	}

	if (p2->HasHitBox())
	{
		delete(p2->UsedHitbox());
	}
	delete(p1);
	delete(entity1);
	delete(p2);
	delete(entity2);
	delete(groundEntity);
	delete(camera);

	delete(m1);
	delete(m2);
	delete(groundMat);
	delete(transparentMat);

	delete(healthBarMesh1);
	delete(healthBarMesh2);
	delete(healthBarMaterial1);
	delete(healthBarMaterial2);
	delete(healthBarEntity1);
	delete(healthBarEntity2);
	
	for (int i = 0; i < 10; i++)
	{
		delete(projMeshes[i]);
		delete(projEntities[i]);
		
	}
	for(int i = 0; i < projectiles.size() ; i++)
	{
		delete(projectiles[i]);
	}

	int projQueueSize = projQueue.size();
	for (int i = 0;i < projQueueSize; i++)
	{
		Projectile* proj = projQueue.front();
		delete(proj);
		projQueue.pop();
	}
	

	for (int i = 0; i < 5; i++)
	{
		delete(jabMeshes[i]);
		delete(jabEntities[i]);
		delete(dTiltMeshes[i]);
		delete(dTiltEntities[i]);
		delete(fTiltMeshes[i]);
		delete(fTiltEntities[i]);
		delete(uTiltMeshes[i]);
		delete(uTiltEntities[i]);
		delete(dAirMeshes[i]);
		delete(dAirEntities[i]);
		delete(nullMeshes[i]);
		delete(nullEntities[i]);
	}

	int jabQueueSize = (int)jabQueue.size();
	for (int i = 0;i < jabQueueSize; i++)
	{
		Hitbox* hb = jabQueue.front();
		delete(hb);
		jabQueue.pop();
	}

	int dTiltQueueSize = (int)dTiltQueue.size();
	for (int i = 0;i < dTiltQueueSize; i++)
	{
		Hitbox* hb = dTiltQueue.front();
		delete(hb);
		dTiltQueue.pop();
	}

	int fTiltQueueSize = (int)fTiltQueue.size();
	for (int i = 0;i < fTiltQueueSize; i++)
	{
		Hitbox* hb = fTiltQueue.front();
		delete(hb);
		fTiltQueue.pop();
	}

	int uTiltQueueSize = (int)uTiltQueue.size();
	for (int i = 0;i < uTiltQueueSize; i++)
	{
		Hitbox* hb = uTiltQueue.front();
		delete(hb);
		uTiltQueue.pop();
	}

	int dAirQueueSize = (int)dAirQueue.size();
	for (int i = 0;i < uTiltQueueSize; i++)
	{
		Hitbox* hb = dAirQueue.front();
		delete(hb);
		dAirQueue.pop();
	}


	int inputQueueSize = (int)inputQueue.size();
	for (int i = 0; i < inputQueueSize; i++)
	{
		InputRegister* IR = inputQueue.front();
		delete(IR);
		inputQueue.pop();
	}
	int inputLogSize1 = (int)InputLog1.size();
	for (int i = 0; i < inputLogSize1; i++)
	{
		delete(InputLog1[i]);
	}
	int inputLogSize2 = (int)InputLog2.size();
	for (int i = 0; i < inputLogSize2; i++)
	{
		delete(InputLog2[i]);
	}
	int nullQueueSize = (int)nullQueue.size();
	for (int i = 0; i < nullQueueSize; i++)
	{
		Hitbox* hb = nullQueue.front();
		delete(hb);
		nullQueue.pop();
	}
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateBasicGeometry();
	
	for (int i = 0; i < 25; i++)
	{
		InputRegister* IR = new InputRegister();
		inputQueue.push(IR);
	}
	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	unsigned int size = sizeof(VertexShaderExternalData);
	size = (size + 15) / 16 * 16;

	//describe buffer

	D3D11_BUFFER_DESC cbDesc = {};
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.ByteWidth = size;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;

	device->CreateBuffer(&cbDesc, 0, constBufferVS.GetAddressOf());
	PrintHealth();
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files
// and also created the Input Layout that describes our 
// vertex data to the rendering pipeline. 
// - Input Layout creation is done here because it must 
//    be verified against vertex shader byte code
// - We'll have that byte code already loaded below
// --------------------------------------------------------
void Game::LoadShaders()
{
	// Blob for reading raw data
	// - This is a simplified way of handling raw data
	ID3DBlob* shaderBlob;

	// Read our compiled vertex shader code into a blob
	// - Essentially just "open the file and plop its contents here"
	D3DReadFileToBlob(
		GetFullPathTo_Wide(L"VertexShader.cso").c_str(), // Using a custom helper for file paths
		&shaderBlob);

	// Create a vertex shader from the information we
	// have read into the blob above
	// - A blob can give a pointer to its contents, and knows its own size
	device->CreateVertexShader(
		shaderBlob->GetBufferPointer(), // Get a pointer to the blob's contents
		shaderBlob->GetBufferSize(),	// How big is that data?
		0,								// No classes in this shader
		vertexShader.GetAddressOf());	// The address of the ID3D11VertexShader*


	// Create an input layout that describes the vertex format
	// used by the vertex shader we're using
	//  - This is used by the pipeline to know how to interpret the raw data
	//     sitting inside a vertex buffer
	//  - Doing this NOW because it requires a vertex shader's byte code to verify against!
	//  - Luckily, we already have that loaded (the blob above)
	D3D11_INPUT_ELEMENT_DESC inputElements[2] = {};

	// Set up the first element - a position, which is 3 float values
	inputElements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;				// Most formats are described as color channels; really it just means "Three 32-bit floats"
	inputElements[0].SemanticName = "POSITION";							// This is "POSITION" - needs to match the semantics in our vertex shader input!
	inputElements[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;	// How far into the vertex is this?  Assume it's after the previous element

	// Set up the second element - a color, which is 4 more float values
	inputElements[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;			// 4x 32-bit floats
	inputElements[1].SemanticName = "COLOR";							// Match our vertex shader input!
	inputElements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;	// After the previous element

	// Create the input layout, verifying our description against actual shader code
	device->CreateInputLayout(
		inputElements,					// An array of descriptions
		2,								// How many elements in that array
		shaderBlob->GetBufferPointer(),	// Pointer to the code of a shader that uses this layout
		shaderBlob->GetBufferSize(),	// Size of the shader code that uses this layout
		inputLayout.GetAddressOf());	// Address of the resulting ID3D11InputLayout*



	// Read and create the pixel shader
	//  - Reusing the same blob here, since we're done with the vert shader code
	D3DReadFileToBlob(
		GetFullPathTo_Wide(L"PixelShader.cso").c_str(), // Using a custom helper for file paths
		&shaderBlob);

	device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		0,
		pixelShader.GetAddressOf());
}



// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	// Create some temporary variables to represent colors
	// - Not necessary, just makes things more readable
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	XMFLOAT4 cornflower = XMFLOAT4(0.4f, 0.6f, 0.75f, 0.0f);
	XMFLOAT4 purple = XMFLOAT4(0.41f, 0.05f, 0.68f, 1.0f);
	XMFLOAT4 transparent = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	XMFLOAT4 white = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	Vertex vertices1[] =
	{
		{ XMFLOAT3(-0.15f, +0.3f, +0.0f), red },
		{ XMFLOAT3(+0.15f, +0.3f, +0.0f), green },
		{ XMFLOAT3(+0.15f, -0.15f, +0.0f), blue },
		{ XMFLOAT3(-0.15f, -0.15f, +0.0f), green },

	};
	Vertex vertices2[] =
	{
		{ XMFLOAT3(-0.15f, +0.3f, +0.0f), green },
		{ XMFLOAT3(+0.15f, +0.3f, +0.0f), blue },
		{ XMFLOAT3(+0.15f, -0.15f, +0.0f), red },
		{ XMFLOAT3(-0.15f, -0.15f, +0.0f), blue },

	};
	
	Vertex groundVerts[] =
	{
		{ XMFLOAT3(-10.0f, -0.15f, +0.0f), green },
		{ XMFLOAT3(+10.0f, -0.15f, +0.0f), green },
		{ XMFLOAT3(-10.0f, -4.35f, +0.0f), green },
		{ XMFLOAT3(+10.0f, -4.35f, +0.0f), green },

	};
	
	Vertex healthBarVerts[] = 
	{
		{ XMFLOAT3(-0.5f, +0.65f, +0.0f), white},
		{ XMFLOAT3(+0.5f, +0.65f, +0.0f), white},
		{ XMFLOAT3(+0.5f, 0.45f, +0.0f), white},
		{ XMFLOAT3(-0.5f, 0.45f, +0.0f), white},

	};

#pragma region Players and Ground and health bars
	unsigned int indices[] = { 0,1,2,0,2,3 };

	mesh1 = new Mesh(vertices1, 4, indices, 6, device);
	mesh2 = new Mesh(vertices2, 4, indices, 6, device);
	groundMesh = new Mesh(groundVerts, 4, indices, 6, device);
	healthBarMesh1 = new Mesh(healthBarVerts, 4, indices, 6, device);
	healthBarMesh2 = new Mesh(healthBarVerts, 4, indices, 6, device);

	m1 = new Material({ 0.3f,0.8f,0.6f,1.0f }, pixelShader, vertexShader);
	m2 = new Material({ 0.9f,0.2f,0.2f,1.0f }, pixelShader, vertexShader);
	groundMat = new Material({ 1.0f,1.0f,1.0f,1.0f }, pixelShader, vertexShader);
	transparentMat = new Material({ 1.0f,1.0f,1.0f,0.0f }, pixelShader, vertexShader);
	healthBarMaterial1 = new Material({ 0.0f,1.0f,0.0f,0.0f }, pixelShader, vertexShader);
	healthBarMaterial2 = new Material({ 0.0f,1.0f,0.0f,0.0f }, pixelShader, vertexShader);

	entity1 = new Entity(mesh1, m1);
	entity2 = new Entity(mesh2, m2);

	groundEntity = new Entity(groundMesh, groundMat);
	p1 = new Player(entity1, 100, false);
	p1->GetEntity()->GetTransform()->setPosition(-0.5f, 0.0f, 0.0f);
	p2 = new Player(entity2, 100, true);
	p2->GetEntity()->GetTransform()->setPosition(0.5f, 0.0f, 0.0f);
	players[0] = p1;
	players[1] = p2;

	healthBarEntity1 = new Entity(healthBarMesh1,healthBarMaterial1);
	healthBarEntity1->GetTransform()->setPosition(-0.8f, 0.6f, +0.0f);
	healthBarEntity2 = new Entity(healthBarMesh2, healthBarMaterial2);
	healthBarEntity2->GetTransform()->setPosition(+0.8f, 0.6f, +0.0f);
	healthBars[0] = healthBarEntity1;
	healthBars[1] = healthBarEntity2;
#pragma endregion



#pragma region HitBox Loading
	//projectile loading and queue loading
	for (int i = 0; i < 10; i++)
	{
		Vertex vertsProj[] =
		{
		{ XMFLOAT3(-0.05f, +0.05f, +0.0f), red },
		{ XMFLOAT3(+0.05f, +0.05f, +0.0f), red },
		{ XMFLOAT3(+0.05f, -0.05f, +0.0f), red },
		{ XMFLOAT3(-0.05f, -0.05f, +0.0f), blue },

		};
		Mesh* pMesh = new Mesh(vertsProj, 4, indices, 6, device);
		projMeshes[i] = pMesh;
	}
	for (int i = 0; i < 10; i++)
	{
		Entity* pEntity = new Entity(projMeshes[i], groundMat);
		projEntities[i] = pEntity;
	}

	for (int i = 0; i < 10; i++)
	{
		Projectile* proj = new Projectile(projEntities[i], 10);
		projQueue.push(proj);
	}

	//jab loading and queue loading
	for (int i = 0; i < 5; i++)
	{

		Vertex jabVerts[] =
		{
		{ XMFLOAT3(-0.07f, +0.06f, +0.0f), blue },
		{ XMFLOAT3(+0.07f, +0.06f, +0.0f), green },
		{ XMFLOAT3(+0.07f, -0.06f, +0.0f), green },
		{ XMFLOAT3(-0.07f, -0.06f, +0.0f), blue },
		};
		Mesh* jMesh = new Mesh(jabVerts, 4, indices, 6, device);
		jabMeshes[i] = jMesh;
	}
	for (int i = 0; i < 5; i++)
	{
		Entity* jEntity = new Entity(jabMeshes[i], groundMat);
		jabEntities[i] = jEntity;
	}

	for (int i = 0; i < 5; i++)
	{
		Hitbox* hb = new Hitbox(jabEntities[i],10,XMFLOAT3(0.20f,0.30f,0.0f),4.0f,12.0f,8.0f,hitboxes::jab);
		jabQueue.push(hb);
	}

	//now for down tilts
	for (int i = 0; i < 5; i++)
	{

		Vertex dTiltVerts[] =
		{
		{ XMFLOAT3(-0.2f, -0.06f, +0.0f), blue },
		{ XMFLOAT3(+0.2f, -0.06f, +0.0f), green },
		{ XMFLOAT3(+0.2f, -0.2f, +0.0f), green },
		{ XMFLOAT3(-0.2f, -0.2f, +0.0f), blue },
		};
		Mesh* dMesh = new Mesh(dTiltVerts, 4, indices, 6, device);
		dTiltMeshes[i] = dMesh;
	}
	for (int i = 0; i < 5; i++)
	{
		Entity* dEntity = new Entity(dTiltMeshes[i], groundMat);
		dTiltEntities[i] = dEntity;
	}

	for (int i = 0; i < 5; i++)
	{
		Hitbox* hb = new Hitbox(dTiltEntities[i], 8, XMFLOAT3(0.10f, 0.450f, 0.0f), 4.0f, 12.0f, 8.0f, hitboxes::dtilt);
		dTiltQueue.push(hb);
	}

	//now forward tilts
	for (int i = 0; i < 5; i++)
	{

		Vertex fTiltVerts[] =
		{
		{ XMFLOAT3(-0.15f, +0.02f, +0.0f), blue },
		{ XMFLOAT3(+0.15f, +0.02f, +0.0f), green },
		{ XMFLOAT3(+0.15f, -0.1f, +0.0f), green },
		{ XMFLOAT3(-0.15f, -0.1f, +0.0f), blue },
		};
		Mesh* fMesh = new Mesh(fTiltVerts, 4, indices, 6, device);
		fTiltMeshes[i] = fMesh;
	}
	for (int i = 0; i < 5; i++)
	{
		Entity* fEntity = new Entity(fTiltMeshes[i], groundMat);
		fTiltEntities[i] = fEntity;
	}

	for (int i = 0; i < 5; i++)
	{
		Hitbox* hb = new Hitbox(fTiltEntities[i], 12, XMFLOAT3(0.40f, 0.10f, 0.0f), 5.0f, 16.0f, 6.0f, hitboxes::ftilt);
		fTiltQueue.push(hb);
	}

	//now up tilts
	for (int i = 0; i < 5; i++)
	{

		Vertex uTiltVerts[] =
		{
		{ XMFLOAT3(-0.12f, +0.5f, +0.0f), blue },
		{ XMFLOAT3(+0.12f, +0.5f, +0.0f), green },
		{ XMFLOAT3(+0.12f, +0.2f, +0.0f), green },
		{ XMFLOAT3(-0.12f, +0.2f, +0.0f), blue },
		};
		Mesh* uMesh = new Mesh(uTiltVerts, 4, indices, 6, device);
		uTiltMeshes[i] = uMesh;
	}
	for (int i = 0; i < 5; i++)
	{
		Entity* uEntity = new Entity(uTiltMeshes[i], groundMat);
		uTiltEntities[i] = uEntity;
	}

	for (int i = 0; i < 5; i++)
	{
		Hitbox* hb = new Hitbox(uTiltEntities[i], 12, XMFLOAT3(0.10f, 0.60f, 0.0f), 3.0f, 10.0f, 4.0f, hitboxes::utilt);
		uTiltQueue.push(hb);
	}

	//down airials
	for (int i = 0; i < 5; i++)
	{
		Vertex dAirVerts[] =
		{
			{ XMFLOAT3(-0.15f, +0.3f, +0.0f), purple },
			{ XMFLOAT3(+0.15f, +0.3f, +0.0f), blue },
			{ XMFLOAT3(+0.15f, -0.15f, +0.0f), purple },
			{ XMFLOAT3(-0.15f, -0.15f, +0.0f), blue },

		};
		Mesh* dAMesh = new Mesh(dAirVerts, 4, indices, 6, device);
		dAirMeshes[i] = dAMesh;
	}
	for (int i = 0; i < 5; i++)
	{
		Entity* dAEntity = new Entity(dAirMeshes[i], groundMat);
		dAirEntities[i] = dAEntity;
	}

	for (int i = 0; i < 5; i++)
	{
		Hitbox* hb = new Hitbox(dAirEntities[i], 15, XMFLOAT3(0.30f, 0.50f, 0.0f), 6.0f, 20.0f, 30.0f, hitboxes::dair);
		dAirQueue.push(hb);
	}

	//null tilts, for actions that do not have a hitbox
	for(int i = 0; i < 5; i++)
	{
		Vertex nullVerts[] =
		{
		{ XMFLOAT3(-0.0f, +0.00f, +0.0f), transparent },
		{ XMFLOAT3(+0.0f, +0.00f, +0.0f), transparent },
		{ XMFLOAT3(+0.0f, -0.0f, +0.0f), transparent },
		{ XMFLOAT3(-0.0f, -0.0f, +0.0f), transparent },
		};
		Mesh* nMesh = new Mesh(nullVerts, 4, indices, 6, device);
		nullMeshes[i] = nMesh;
	}
	for (int i = 0; i < 5; i++)
	{
		Entity* nEntity = new Entity(nullMeshes[i], groundMat);
		nullEntities[i] = nEntity;
	}

	for (int i = 0; i < 5; i++)
	{
		Hitbox* hb = new Hitbox(nullEntities[i], 0, XMFLOAT3(0.00f, 0.0f, 0.0f), 2.0f, 30.0f, 6.0f, hitboxes::null);
		nullQueue.push(hb);
	}

#pragma endregion

	


}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();
	camera->UpdateProjectionMatrix((float)width / height);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

#pragma region P1 Game Logic
	//game logic for p1

#pragma region Register Inputs
	if ((GetAsyncKeyState('W') & 0x8000) && !p1Up)
	{
		InputRegister* ir = inputQueue.front();
		ir->SetInput(inputs::up);
		InputLog1.push_back(ir);
		inputQueue.pop();
	}
	if ((GetAsyncKeyState('A') & 0x8000) && !p1Left)
	{
		InputRegister* ir = inputQueue.front();
		ir->SetInput(inputs::left);
		InputLog1.push_back(ir);
		inputQueue.pop();
	}
	if ((GetAsyncKeyState('S') & 0x8000) && !p1Down)
	{
		InputRegister* ir = inputQueue.front();
		ir->SetInput(inputs::down);
		InputLog1.push_back(ir);
		inputQueue.pop();
	}
	if ((GetAsyncKeyState('D') & 0x8000) && !p1Right)
	{
		InputRegister* ir = inputQueue.front();
		ir->SetInput(inputs::right);
		InputLog1.push_back(ir);
		inputQueue.pop();
	}

	p1Up = GetAsyncKeyState('W');
	p1Left = GetAsyncKeyState('A');
	p1Down = GetAsyncKeyState('S');
	p1Right = GetAsyncKeyState('D');

#pragma endregion



	if (!p1Starting && !p1Active && !p1End)
	{
		
		//projectile firing for 1
		/*
		if (GetAsyncKeyState('C') & 0x8000 && !fired1)
		{
			projQueue.front()->Shot(p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().x,
				p1->GetEntity()->GetTransform()->getPosition().y);
			projQueue.front()->SetOwner(true);
			projectiles.push_back(projQueue.front());
			projQueue.pop();
			fired1 = GetAsyncKeyState('C');
			p1->SetFrames(nullQueue.front());
			nullQueue.pop();
			p1->UsedHitbox()->SetTransform(p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().y);
			p1Starting = true;
		}
		*/
		if(GetAsyncKeyState('X') & 0x8000 && !attacked1)
		{
			if(p1->isGrounded())
			{ 
				//check for custom inputs
				if (InputLog1.size() >= 2)
			{
				switch (InputLog1[0]->GetInput())
				{
				case inputs::down:
				{
					switch (InputLog1[1]->GetInput())
						{
						case inputs::right:
						{
							if (facingRight())
							{
								projQueue.front()->Shot(p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().x,
									p1->GetEntity()->GetTransform()->getPosition().y);
								projQueue.front()->SetOwner(true);
								projectiles.push_back(projQueue.front());
								projQueue.pop();
								p1->SetFrames(nullQueue.front());
								nullQueue.pop();
								p1->UsedHitbox()->SetTransform(p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().y);
								p1Starting = true;
							}
						}
						break;
						case inputs::left:
						{
							if (!facingRight())
							{
								projQueue.front()->Shot(p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().x,
									p1->GetEntity()->GetTransform()->getPosition().y);
								projQueue.front()->SetOwner(true);
								projectiles.push_back(projQueue.front());
								projQueue.pop();
								p1->SetFrames(nullQueue.front());
								nullQueue.pop();
								p1->UsedHitbox()->SetTransform(p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().y);
								p1Starting = true;
							}
						}
						break;
						}

				}
				break;
				}
			}

				//all the inputs that are not customs
				if (!p1Starting) {

					if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
					{
						p1->SetFrames(fTiltQueue.front());
						fTiltQueue.pop();
					}
					else if (GetAsyncKeyState('S') & 0x8000)
					{
						p1->SetFrames(dTiltQueue.front());
						dTiltQueue.pop();
					}
					else if (GetAsyncKeyState('W') & 0x8000)
					{
						p1->SetFrames(uTiltQueue.front());
						uTiltQueue.pop();
					}
					else
					{
						p1->SetFrames(jabQueue.front());
						jabQueue.pop();
					}
					p1->UsedHitbox()->SetTransform(p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().y);
				}
				
			}
			else
			{
				if (!p1Starting)
				{
					if (GetAsyncKeyState('S') & 0x8000)
					{
						p1->SetFrames(dAirQueue.front());
						dAirQueue.pop();
						p1->UsedHitbox()->SetTransform(p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().y);
					}
				}
			}
			p1Starting = true;
		}
		attacked1 = GetAsyncKeyState('X');
	}
	else if (p1Starting)
	{
		p1Frames+= (deltaTime* 60.0f);
		if (p1Frames >= p1->GetStart())
		{
			p1Frames = 0;
			p1Starting = false;
			p1Active = true;
		}
	}
	else if (p1Active)
	{
		p1Frames+= (deltaTime * 60.0f);
		if (!p2Hit && p1->UsedHitbox()->isColliding(p2->GetEntity()))
		{
			p2->Damage(p1->UsedHitbox()->GetDamage());
			p1Hit = true;
			PrintHealth();
			PlayerHit(true);
		}
		if (p1Frames >= p1->GetActive())
		{
			p1Frames = 0;
			p1Active = false;
			p1End = true;
		}
	}
	else if (p1End)
	{
		p1Frames+= (deltaTime * 60.0f);
		if (p1Frames >= p1->GetEnd())
		{
			p1Frames = 0;
			p1End = false;
			p1Hit = false;
			
			switch (p1->UsedHitbox()->Type())
			{
			case hitboxes::jab:
				{
				Hitbox* hb = p1->UsedHitbox();
				jabQueue.push(hb);
				p1->ResetFrames();
				hb = nullptr;
				}
				break;

			case hitboxes::dtilt:
				{
				
				Hitbox* hb = p1->UsedHitbox();
				dTiltQueue.push(hb);
				p1->ResetFrames();
				hb = nullptr;
				}
				break;
			case hitboxes::ftilt:
				{
				Hitbox* hb = p1->UsedHitbox();
				fTiltQueue.push(hb);
				p1->ResetFrames();
				hb = nullptr;
				}
			break;
			case hitboxes::utilt:
			{
				Hitbox* hb = p1->UsedHitbox();
				uTiltQueue.push(hb);
				p1->ResetFrames();
				hb = nullptr;
			}
			break;
			case hitboxes::dair:
			{
				Hitbox* hb = p1->UsedHitbox();
				dAirQueue.push(hb);
				p1->ResetFrames();
				hb = nullptr;
			}
			break;
			case hitboxes::null:
			{
				Hitbox* hb = p1->UsedHitbox();
				nullQueue.push(hb);
				p1->ResetFrames();
				hb = nullptr;
			}
			break;
			
			}

		}
	}
	p1->Update(deltaTime);
#pragma endregion

#pragma region P2GameLogic
	//game logic for p2

	//Register inputs
#pragma region Register Inputs
	if ((GetAsyncKeyState('I') & 0x8000) && !p2Up)
	{
		InputRegister* ir = inputQueue.front();
		ir->SetInput(inputs::up);
		InputLog2.push_back(ir);
		inputQueue.pop();
	}
	if ((GetAsyncKeyState('J') & 0x8000) && !p2Left)
	{
		InputRegister* ir = inputQueue.front();
		ir->SetInput(inputs::left);
		InputLog2.push_back(ir);
		inputQueue.pop();
	}
	if ((GetAsyncKeyState('K') & 0x8000) && !p2Down)
	{
		InputRegister* ir = inputQueue.front();
		ir->SetInput(inputs::down);
		InputLog2.push_back(ir);
		inputQueue.pop();
	}
	if ((GetAsyncKeyState('L') & 0x8000) && !p2Right)
	{
		InputRegister* ir = inputQueue.front();
		ir->SetInput(inputs::right);
		InputLog2.push_back(ir);
		inputQueue.pop();
	}
	p2Up = GetAsyncKeyState('I');
	p2Left = GetAsyncKeyState('J');
	p2Down = GetAsyncKeyState('K');
	p2Right = GetAsyncKeyState('L');
#pragma endregion
	if (!p2Starting && !p2Active && !p2End)
	{

		/*
		//projectile firing for 2
		if (GetAsyncKeyState('N') & 0x8000 && !fired2)
		{
			projQueue.front()->Shot(p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().x,
				p2->GetEntity()->GetTransform()->getPosition().y);
			projQueue.front()->SetOwner(false);
			projectiles.push_back(projQueue.front());
			projQueue.pop();
			p2->SetFrames(nullQueue.front());
			nullQueue.pop();
			p2->UsedHitbox()->SetTransform(p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().y);
			p2Starting = true;
		}
		*/
		if (GetAsyncKeyState('M') & 0x8000 && !attacked2)
		{
			if (p2->isGrounded())
			{
				//check for custom inputs
				if (InputLog2.size() >= 2)
				{
					switch (InputLog2[0]->GetInput())
					{
					case inputs::down:
					{

						switch (InputLog2[1]->GetInput())
						{
						case inputs::right:
						{
							if (!facingRight())
							{
								projQueue.front()->Shot(p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().x,
									p2->GetEntity()->GetTransform()->getPosition().y);
								projQueue.front()->SetOwner(false);
								projectiles.push_back(projQueue.front());
								projQueue.pop();
								p2->SetFrames(nullQueue.front());
								nullQueue.pop();
								p2->UsedHitbox()->SetTransform(p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().y);
								p2Starting = true;
							}
						}
						break;
						case inputs::left:
						{
							if (facingRight())
							{
								projQueue.front()->Shot(p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().x,
									p2->GetEntity()->GetTransform()->getPosition().y);
								projQueue.front()->SetOwner(false);
								projectiles.push_back(projQueue.front());
								projQueue.pop();
								p2->SetFrames(nullQueue.front());
								nullQueue.pop();
								p2->UsedHitbox()->SetTransform(p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().y);
								p2Starting = true;
							}
						}
						break;
						}

					}
					break;
					}
				}

				//all of p2's base inouts
				if (!p2Starting)
				{
					if ((GetAsyncKeyState('J') & 0x8000) || (GetAsyncKeyState('L') & 0x8000))
					{
						p2->SetFrames(fTiltQueue.front());
						fTiltQueue.pop();
					}
					else if (GetAsyncKeyState('K') & 0x8000)
					{
						p2->SetFrames(dTiltQueue.front());
						dTiltQueue.pop();
					}
					else if (GetAsyncKeyState('I') & 0x8000)
					{
						p2->SetFrames(uTiltQueue.front());
						uTiltQueue.pop();
					}
					else
					{
						p2->SetFrames(jabQueue.front());
						jabQueue.pop();
					}
					p2->UsedHitbox()->SetTransform(p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().y);

				}
				
			}
			else
			{
				if (GetAsyncKeyState('K') & 0x8000)
				{
					p2->SetFrames(dAirQueue.front());
					dAirQueue.pop();
					p2->UsedHitbox()->SetTransform(p2->GetEntity()->GetTransform()->getPosition().x, p1->GetEntity()->GetTransform()->getPosition().x, p2->GetEntity()->GetTransform()->getPosition().y);
				}
			}
			p2Starting = true;
		}
		fired2 = GetAsyncKeyState('N');
		attacked2 = GetAsyncKeyState('M');
	}
	else if (p2Starting)
	{
		p2Frames += (deltaTime * 60.0f);
		if (p2Frames >= p2->GetStart())
		{
			p2Frames = 0;
			p2Starting = false;
			p2Active = true;
		}
	}
	else if (p2Active)
	{
		p2Frames += (deltaTime * 60.0f);
		if (!p2Hit && p2->UsedHitbox()->isColliding(p1->GetEntity()))
		{
			p1->Damage(p2->UsedHitbox()->GetDamage());
			p2Hit = true;
			PrintHealth();
			PlayerHit(false);
		}

		if (p2Frames >= p2->GetActive())
		{
			p2Frames = 0;
			p2Active = false;
			p2End = true;

		}
	}
	else if (p2End)
	{
		p2Frames += (deltaTime * 60.0f);
		if (p2Frames >= p2->GetEnd())
		{
			p2Frames = 0;
			p2End = false;
			p2Hit = false;
			switch (p2->UsedHitbox()->Type())
			{
			case hitboxes::jab:
			{
				Hitbox* hb = p2->UsedHitbox();
				jabQueue.push(hb);
				p2->ResetFrames();
				hb = nullptr;
			}
			break;

			case hitboxes::dtilt:
			{

				Hitbox* hb = p2->UsedHitbox();
				dTiltQueue.push(hb);
				p2->ResetFrames();
				hb = nullptr;
			}
			break;
			case hitboxes::ftilt:
			{
				Hitbox* hb = p2->UsedHitbox();
				fTiltQueue.push(hb);
				p2->ResetFrames();
				hb = nullptr;
			}

			case hitboxes::utilt:
			{
				Hitbox* hb = p2->UsedHitbox();
				uTiltQueue.push(hb);
				p2->ResetFrames();
				hb = nullptr;
			}
			break;
			case hitboxes::dair:
			{
				Hitbox* hb = p2->UsedHitbox();
				dAirQueue.push(hb);
				p2->ResetFrames();
				hb = nullptr;
			}
			break;
			case hitboxes::null:
			{
				Hitbox* hb = p2->UsedHitbox();
				nullQueue.push(hb);
				p2->ResetFrames();
				hb = nullptr;
			}
			break;
			}
		}
	}
	p2->Update(deltaTime);
#pragma endregion

	
#pragma region Projectile Update
	//update projectiles
	for (int i = 0; i < projectiles.size(); i++)
	{
		//checks to see if projectile is active before running logic (temporary work around)
		if (projectiles[i]->GetActive() == true)
		{
			projectiles[i]->Update(deltaTime);
			//checks to see whehter collision should be checked with p1 or p2
			if (projectiles[i]->GetOwner())
			{
				//collision check for p2
				if (projectiles[i]->isColliding(p2->GetEntity()))
				{
					p2->Damage(projectiles[i]->GetDamage());
					projectiles[i]->SetActive(false);
					PrintHealth();
					projQueue.push(projectiles[i]);
					projectiles.erase(projectiles.begin() + i);
				}
			}
			
			else
			{
				//collision check for p1
				if (projectiles[i]->isColliding(p1->GetEntity()))
				{
					p1->Damage(projectiles[i]->GetDamage());
					projectiles[i]->SetActive(false);
					PrintHealth();
					projQueue.push(projectiles[i]);
					projectiles.erase(projectiles.begin() + i);
				}
			}
		}
	}
#pragma endregion
#pragma region Input Update
	bool deleteInputFront1 = false;
	for (int i = 0; i < InputLog1.size(); i++)
	{
		if (!(InputLog1[i]->Update(deltaTime)))
		{
			deleteInputFront1 = true;
		}
	}
	if (deleteInputFront1)
	{
		inputQueue.push(InputLog1[0]);
		InputLog1.erase(InputLog1.begin());
	}

	bool deleteInputFront2 = false;
	for (int i = 0; i < InputLog2.size(); i++)
	{
		if (!(InputLog2[i]->Update(deltaTime)))
		{
			deleteInputFront2 = true;
		}
	}
	if (deleteInputFront2)
	{
		inputQueue.push(InputLog2[0]);
		InputLog2.erase(InputLog2.begin());
	}
#pragma endregion

	
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };


	// Clear the render target and depth buffer (erases what's on the screen)
//  - Do this ONCE PER FRAME
//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV.Get(), color);
	context->ClearDepthStencilView(
		depthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	VertexShaderExternalData vsData;

#pragma region Ground Render
	//Render the ground
	vsData.view = camera->GetViewMatrix();
	vsData.projection = camera->GetProjectionMatrix();

	//shader decleration
	vsData.colorTint = groundEntity->GetMaterial()->GetColorTint();
	vsData.world = groundEntity->GetTransform()->GetWorldMatrix();

	D3D11_MAPPED_SUBRESOURCE mappedBuffer = {};
	context->Map(constBufferVS.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuffer);

	memcpy(mappedBuffer.pData, &vsData, sizeof(vsData));

	context->Unmap(constBufferVS.Get(), 0);

	context->VSSetConstantBuffers(0, 1, constBufferVS.GetAddressOf());

	context->VSSetShader(groundEntity->GetMaterial()->GetVertexShader().Get(), 0, 0);
	context->PSSetShader(groundEntity->GetMaterial()->GetPixelShader().Get(), 0, 0);

	context->IASetInputLayout(inputLayout.Get());

	UINT stride = sizeof(Vertex);
	UINT offset = 0;


	context->IASetVertexBuffers(0, 1, groundEntity->GetMesh()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(groundEntity->GetMesh()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(groundEntity->GetMesh()->getIndecesies(), 0, 0);

#pragma endregion

	
	//draw players
	for (int i = 0; i < 2; i++)
	{
		vsData.view = camera->GetViewMatrix();
		vsData.projection = camera->GetProjectionMatrix();

		//shader decleration
		vsData.colorTint = players[i]->GetEntity()->GetMaterial()->GetColorTint();
		vsData.world = players[i]->GetEntity()->GetTransform()->GetWorldMatrix();

		D3D11_MAPPED_SUBRESOURCE mappedBuffer = {};
		context->Map(constBufferVS.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuffer);

		memcpy(mappedBuffer.pData, &vsData, sizeof(vsData));

		context->Unmap(constBufferVS.Get(), 0);

		context->VSSetConstantBuffers(0, 1, constBufferVS.GetAddressOf());

		// Set the vertex and pixel shaders to use for the next Draw() command
		//  - These don't technically need to be set every frame
		//  - Once you start applying different shaders to different objects,
		//    you'll need to swap the current shaders before each draw
		context->VSSetShader(players[i]->GetEntity()->GetMaterial()->GetVertexShader().Get(), 0, 0);
		context->PSSetShader(players[i]->GetEntity()->GetMaterial()->GetPixelShader().Get(), 0, 0);


		// Ensure the pipeline knows how to interpret the data (numbers)
		// from the vertex buffer.  
		// - If all of your 3D models use the exact same vertex layout,
		//    this could simply be done once in Init()
		// - However, this isn't always the case (but might be for this course)
		context->IASetInputLayout(inputLayout.Get());


		// Set buffers in the input assembler
		//  - Do this ONCE PER OBJECT you're drawing, since each object might
		//    have different geometry.
		//  - for this demo, this step *could* simply be done once during Init(),
		//    but I'm doing it here because it's often done multiple times per frame
		//    in a larger application/game
		UINT stride = sizeof(Vertex);
		UINT offset = 0;


		context->IASetVertexBuffers(0, 1, players[i]->GetEntity()->GetMesh()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		context->IASetIndexBuffer(players[i]->GetEntity()->GetMesh()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
		context->DrawIndexed(players[i]->GetEntity()->GetMesh()->getIndecesies(), 0, 0);
		
		if (players[i]->HasHitBox())
		{
			if ((i == 0 && p1Active) || (i == 1 && p2Active))
			{
				vsData.view = camera->GetViewMatrix();
				vsData.projection = camera->GetProjectionMatrix();

				//shader decleration
				vsData.colorTint = players[i]->UsedHitbox()->GetEntity()->GetMaterial()->GetColorTint();
				vsData.world = players[i]->UsedHitbox()->GetEntity()->GetTransform()->GetWorldMatrix();

				D3D11_MAPPED_SUBRESOURCE mappedBuffer = {};
				context->Map(constBufferVS.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuffer);

				memcpy(mappedBuffer.pData, &vsData, sizeof(vsData));

				context->Unmap(constBufferVS.Get(), 0);

				context->VSSetConstantBuffers(0, 1, constBufferVS.GetAddressOf());

				// Set the vertex and pixel shaders to use for the next Draw() command
				//  - These don't technically need to be set every frame
				//  - Once you start applying different shaders to different objects,
				//    you'll need to swap the current shaders before each draw
				context->VSSetShader(players[i]->UsedHitbox()->GetEntity()->GetMaterial()->GetVertexShader().Get(), 0, 0);
				context->PSSetShader(players[i]->UsedHitbox()->GetEntity()->GetMaterial()->GetPixelShader().Get(), 0, 0);


				// Ensure the pipeline knows how to interpret the data (numbers)
				// from the vertex buffer.  
				// - If all of your 3D models use the exact same vertex layout,
				//    this could simply be done once in Init()
				// - However, this isn't always the case (but might be for this course)
				context->IASetInputLayout(inputLayout.Get());


				// Set buffers in the input assembler
				//  - Do this ONCE PER OBJECT you're drawing, since each object might
				//    have different geometry.
				//  - for this demo, this step *could* simply be done once during Init(),
				//    but I'm doing it here because it's often done multiple times per frame
				//    in a larger application/game
				UINT stride = sizeof(Vertex);
				UINT offset = 0;


				context->IASetVertexBuffers(0, 1, players[i]->UsedHitbox()->GetEntity()->GetMesh()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
				context->IASetIndexBuffer(players[i]->UsedHitbox()->GetEntity()->GetMesh()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
				context->DrawIndexed(players[i]->UsedHitbox()->GetEntity()->GetMesh()->getIndecesies(), 0, 0);
			}
		}
	}
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->GetActive() == true)
		{

			
			vsData.view = camera->GetViewMatrix();
			vsData.projection = camera->GetProjectionMatrix();

			//shader decleration
			vsData.colorTint = projectiles[i]->GetEntity()->GetMaterial()->GetColorTint();
			vsData.world = projectiles[i]->GetEntity()->GetTransform()->GetWorldMatrix();

			D3D11_MAPPED_SUBRESOURCE mappedBuffer = {};
			context->Map(constBufferVS.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuffer);

			memcpy(mappedBuffer.pData, &vsData, sizeof(vsData));

			context->Unmap(constBufferVS.Get(), 0);

			context->VSSetConstantBuffers(0, 1, constBufferVS.GetAddressOf());



			// Set the vertex and pixel shaders to use for the next Draw() command
			//  - These don't technically need to be set every frame
			//  - Once you start applying different shaders to different objects,
			//    you'll need to swap the current shaders before each draw
			context->VSSetShader(projectiles[i]->GetEntity()->GetMaterial()->GetVertexShader().Get(), 0, 0);
			context->PSSetShader(projectiles[i]->GetEntity()->GetMaterial()->GetPixelShader().Get(), 0, 0);


			// Ensure the pipeline knows how to interpret the data (numbers)
			// from the vertex buffer.  
			// - If all of your 3D models use the exact same vertex layout,
			//    this could simply be done once in Init()
			// - However, this isn't always the case (but might be for this course)
			context->IASetInputLayout(inputLayout.Get());


			// Set buffers in the input assembler
			//  - Do this ONCE PER OBJECT you're drawing, since each object might
			//    have different geometry.
			//  - for this demo, this step *could* simply be done once during Init(),
			//    but I'm doing it here because it's often done multiple times per frame
			//    in a larger application/game
			UINT stride = sizeof(Vertex);
			UINT offset = 0;


			context->IASetVertexBuffers(0, 1, projectiles[i]->GetEntity()->GetMesh()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
			context->IASetIndexBuffer(projectiles[i]->GetEntity()->GetMesh()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
			context->DrawIndexed(projectiles[i]->GetEntity()->GetMesh()->getIndecesies(), 0, 0);
			
			
		}
	}
	//draw health bars
	for (int i = 0; i < 2; i++)
	{
		vsData.view = camera->GetViewMatrix();
		vsData.projection = camera->GetProjectionMatrix();

		//shader decleration
		vsData.colorTint = healthBars[i]->GetMaterial()->GetColorTint();
		vsData.world = healthBars[i]->GetTransform()->GetWorldMatrix();

		D3D11_MAPPED_SUBRESOURCE mappedBuffer = {};
		context->Map(constBufferVS.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuffer);

		memcpy(mappedBuffer.pData, &vsData, sizeof(vsData));

		context->Unmap(constBufferVS.Get(), 0);

		context->VSSetConstantBuffers(0, 1, constBufferVS.GetAddressOf());

		// Set the vertex and pixel shaders to use for the next Draw() command
		//  - These don't technically need to be set every frame
		//  - Once you start applying different shaders to different objects,
		//    you'll need to swap the current shaders before each draw
		context->VSSetShader(healthBars[i]->GetMaterial()->GetVertexShader().Get(), 0, 0);
		context->PSSetShader(healthBars[i]->GetMaterial()->GetPixelShader().Get(), 0, 0);


		// Ensure the pipeline knows how to interpret the data (numbers)
		// from the vertex buffer.  
		// - If all of your 3D models use the exact same vertex layout,
		//    this could simply be done once in Init()
		// - However, this isn't always the case (but might be for this course)
		context->IASetInputLayout(inputLayout.Get());


		// Set buffers in the input assembler
		//  - Do this ONCE PER OBJECT you're drawing, since each object might
		//    have different geometry.
		//  - for this demo, this step *could* simply be done once during Init(),
		//    but I'm doing it here because it's often done multiple times per frame
		//    in a larger application/game
		UINT stride = sizeof(Vertex);
		UINT offset = 0;


		context->IASetVertexBuffers(0, 1, healthBars[i]->GetMesh()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		context->IASetIndexBuffer(healthBars[i]->GetMesh()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
		context->DrawIndexed(healthBars[i]->GetMesh()->getIndecesies(), 0, 0);
	}

	// Present the back buffer to the user
//  - Puts the final frame we're drawing into the window so the user can see it
//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);

	// Due to the usage of a more sophisticated swap chain,
	// the render target must be re-bound after every call to Present()
	context->OMSetRenderTargets(1, backBufferRTV.GetAddressOf(), depthStencilView.Get());
}

void Game::PrintHealth()
{
	std::cout << std::flush;
	std::cout << "Player 1 Health:  " << p1->GetHealth() << "  Player 2 Health:  " << p2->GetHealth()<<std::endl;
	XMFLOAT4 color1 = healthBarEntity1->GetMaterial()->GetColorTint();
	color1.x = 1.0f - (((float)p1->GetHealth()) / 100.0f);
	color1.y = (((float)p1->GetHealth()) / 100.0f);
	healthBarEntity1->GetMaterial()->SetColorTint(color1);
	healthBarEntity1->GetTransform()->setPosition(-0.4f - ((color1.y) * 0.5f), 0.6f, 0.0f);
	healthBarEntity1->GetTransform()->setScale(color1.y, 1.0f, 1.0f);

	XMFLOAT4 color2 = healthBarEntity2->GetMaterial()->GetColorTint();
	color2.x = 1.0f - (((float)p2->GetHealth()) / 100.0f);
	color2.y = (((float)p2->GetHealth()) / 100.0f);
	healthBarEntity2->GetMaterial()->SetColorTint(color2);
	healthBarEntity2->GetTransform()->setPosition(0.4f + ((color2.y) * 0.5f), 0.6f, 0.0f);
	healthBarEntity2->GetTransform()->setScale(color2.y, 1.0f, 1.0f);

}


void Game::PlayerHit(bool isP1)
{
	float direction = p1->GetEntity()->GetTransform()->getPosition().x - p2->GetEntity()->GetTransform()->getPosition().x;
	bool reverse = direction > 0;
	switch (isP1)
	{
		case true: 
		{
			p1Active = false;
			p1Starting = false;
			p1End = true;
			Hitbox* hb = p1->UsedHitbox();
			/*switch (p1->UsedHitbox()->Type())
			{
				
			case hitboxes::jab:
			{
				if (reverse)
				{
					p2->LaunchPlayer(hb->P2Launch());
				}
				else
				{
					p2->LaunchPlayer(hb->Launch());
				}
				//jabQueue.push(hb);
				hb = nullptr;
			}
			break;

			case hitboxes::dtilt:
			{
				if (reverse)
				{
					p2->LaunchPlayer(hb->P2Launch());
				}
				else
				{
					p2->LaunchPlayer(hb->Launch());
				}

				//dTiltQueue.push(hb);
				hb = nullptr;
			}
			break;

			case hitboxes::ftilt:
			{
				if (reverse)
				{
					p2->LaunchPlayer(hb->P2Launch());
				}
				else
				{
					p2->LaunchPlayer(hb->Launch());
				}
				//fTiltQueue.push(hb);
				hb = nullptr;
			}
			break;

			case hitboxes::utilt:
			{
				if (reverse)
				{
					p2->LaunchPlayer(hb->P2Launch());
				}
				else
				{
					p2->LaunchPlayer(hb->Launch());
				}
				//uTiltQueue.push(hb);
				hb = nullptr;
			}
			break;
			}*/
			if (reverse)
			{
				p2->LaunchPlayer(hb->P2Launch());
			}
			else
			{
				p2->LaunchPlayer(hb->Launch());
			}
			hb = nullptr;

		}
		break;
		
		case false:
		{
			p2Active = false;
			p2Starting = false;
			p2End = true;
			Hitbox* hb = p2->UsedHitbox();
			/*switch (p2->UsedHitbox()->Type())
			{
				
			case hitboxes::jab:
			{
				if (!reverse)
				{
					p1->LaunchPlayer(hb->P2Launch());
				}
				else
				{
					p1->LaunchPlayer(hb->Launch());
				}

				//jabQueue.push(hb);
				hb = nullptr;
			}
			break;

			case hitboxes::dtilt:
			{

				if (!reverse)
				{
					p1->LaunchPlayer(hb->P2Launch());
				}
				else
				{
					p1->LaunchPlayer(hb->Launch());
				}

				//dTiltQueue.push(hb);
				hb = nullptr;
			}
			break;

			case hitboxes::ftilt:
			{

				if (!reverse)
				{
					p1->LaunchPlayer(hb->P2Launch());
				}
				else
				{
					p1->LaunchPlayer(hb->Launch());
				}

				//fTiltQueue.push(hb);
				hb = nullptr;
			}
			break;

			case hitboxes::utilt:
			{

				if (!reverse)
				{
					p1->LaunchPlayer(hb->P2Launch());
				}
				else
				{
					p1->LaunchPlayer(hb->Launch());
				}

				//uTiltQueue.push(hb);
				hb = nullptr;
			}
			break;
			}*/
			if (!reverse)
			{
				p1->LaunchPlayer(hb->P2Launch());
			}
			else
			{
				p1->LaunchPlayer(hb->Launch());
			}
			hb = nullptr;
		}
		break;
	}
	
}

bool Game::facingRight()
{
	return p1->GetEntity()->GetTransform()->getPosition().x - p2->GetEntity()->GetTransform()->getPosition().x < 0;
}


