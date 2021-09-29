#include "Game.h"
#include "Vertex.h"
#include "BufferStruct.h"
//#include "DDSTextureLoader.h"
//#include "WICTextureLoader.h"

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
	camera = new Camera(0, 0.15f, 0, (float)width / height);


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
	
	delete(camera);
	/*
	delete(pixelShader);
	delete(vertexShader);
	delete(pixelNormalShader);
	delete(vertexNormalShader);
	delete(pixelSkyShader);
	delete(vertexSkyShader);

	delete(sky);
	delete(meshSky);
	delete(meshWater);
	delete(mWater);
	delete(water);
	delete(mCannon);
	delete(meshCannon);
	delete(mBoat);
	delete(meshBoat);
	delete(playerBoat);

	for (int i = balls.size() - 1; i >= 0; i--)
	{
		delete(balls[i]);
	}

	for (int i = boats.size() - 1; i >= 0; i--)
	{
		delete(boats[i]);
	}
	*/
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	unsigned int size = sizeof(VertexShaderExternalData);
	size = (size + 15) / 16 * 16;
	/*
	light = { XMFLOAT3(0.4f, 0.2f, 0.33f), 1.0f, XMFLOAT3(1.0f, -1.0f, 0.0f) };
	ambient = XMFLOAT3(0.1f, 0.07f, 0.04f);
	light2 = { XMFLOAT3(0.41f, 0.05f, 0.68f), 1.0f, XMFLOAT3(1.0f, 10.0f, 1.0f) };
	ambient2 = XMFLOAT3(0.1f, 0.07f, 0.04f);
	light3 = { XMFLOAT3(0.4f, 0.6f, 0.75f), 1.0f, XMFLOAT3(-1.0f, 1.0f, 0.0f) };
	ambient3 = XMFLOAT3(0.1f, 0.07f, 0.04f);
	pointLight = { XMFLOAT3(0.5f, 0.2f, 0.83f),1.0f, XMFLOAT3(0.0f, 2.0f, 0.0f) };
	pointAmbient = XMFLOAT3(0.1f, 0.07f, 0.04f);
	*/
	//initialize textures

	//texture1
	
	/*
	D3D11_SAMPLER_DESC sampDesc = {};
	
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	device->CreateSamplerState(&sampDesc, sampler.GetAddressOf());

	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	//LoadShaders();
	*/
	CreateBasicGeometry();

	//std::cout << "Boat Simulator: Press 'A' and 'D' to rotate and click to shoot";
	
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
	/*
	vertexShader = new SimpleVertexShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"VertexShader.cso").c_str());
	pixelShader = new SimplePixelShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"PixelShader.cso").c_str());
	vertexNormalShader = new SimpleVertexShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"NormalMapsVS.cso").c_str());
	pixelNormalShader = new SimplePixelShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"NormalMapsPS.cso").c_str());
	vertexSkyShader = new SimpleVertexShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"SkyBoxVS.cso").c_str());
	pixelSkyShader = new SimplePixelShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"SkyBoxPS.cso").c_str());
	*/
}



// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	/*
	//load meshes
	meshWater = new Mesh(GetFullPathTo("../../Assets/Models/cube.obj").c_str(), device);
	meshSky = new Mesh(GetFullPathTo("../../Assets/Models/cube.obj").c_str(), device);
	meshCannon = new Mesh(GetFullPathTo("../../Assets/Models/sphere.obj").c_str(), device);
	meshBoat = new Mesh(GetFullPathTo("../../Assets/Models/boat.obj").c_str(), device);

	//load materials
	mWater = new Material({1.0f,1.0f,1.0f,1.0f}, pixelShader, vertexShader, 4.0f, textureSRVWater,sampler);
	mCannon = new Material({ 1.0f,1.0f,1.0f,1.0f },pixelNormalShader,vertexNormalShader, 4.0f, textureCannon, sampler, 
		textureCannonNorm, textureCannonRough, textureCannonMetal);
	mBoat = new Material({ 1.0f,1.0f,1.0f,1.0f }, pixelNormalShader, vertexNormalShader, 4.0f, textureBoat, sampler,
		textureBoatNorm, textureBoatRough, textureBoatMetal);

	water = new Entity(meshWater,mWater);
	playerBoat = new Entity(meshBoat, mBoat);

	
	//set scene entities to an array
	entities[0] = water;
	entities[1] = playerBoat;



	water->GetTransform()->setPosition(0.0f, -0.7f, 0.0f);
	
	water->GetTransform()->setScale(150.0f, 1.0f , 150.0f);
	playerBoat->GetTransform()->setScale(0.003f, 0.003f, 0.003f);
	*/

	//sky = new Sky(meshSky, sampler, textureSky, pixelSkyShader, vertexSkyShader, device);
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
	/*
	//fire a cannonball when clicked
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && camera->isFree() == false && !prevMouseClicked && !gameOver)
	{
		Cannonball* cb = new Cannonball(meshCannon, mCannon);
		cb->GetTransform()->setPosition(0,0.15f,0);
		cb->GetTransform()->setRotate(camera->getTransform().getRotation().x, camera->getTransform().getRotation().y, camera->getTransform().getRotation().z);
		cb->GetTransform()->setScale(0.05f, 0.05f, 0.05f);
		balls.push_back(cb);
		
	}

	//updates the cannonballs positions
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->Update(deltaTime);
	}

	//updates the boats positions and checks for collisons
	for (int i = 0; i < boats.size(); i++)
	{
		if (boats[i]->isActive())
		{
			boats[i]->Update(deltaTime);
			for (int j = 0; j < balls.size(); j++)
			{
				//cannonball collisions
				if (boats[i]->isColliding(balls[j])  && balls[j]->isActive())
				{
					boats[i]->setInactive();
					balls[i]->setInactive();
					boatsShot++;
				}
				if (boats[i]->isColliding(playerBoat) )
				{
					/*
					//nullptr CRASH = new *nullptr;
					
					//game over state, remove boats and lock cannon firing
					for (int i = 0; i < boats.size(); i++)
					{
						boats[i]->setInactive();
					}
					if (!gameOver)
					{
						std::cout << "Game Over: You shot " << boatsShot << " boats.";
					}
					gameOver = true;
				}
			}
		}
		
	}

	//code to spawn in boats
	if (rand() % counter == 0 && !gameOver)
	{
		counter--;
		if (counter < 5)
		{
			counter = 5;
		}
		Enemy* enemyBoat = new Enemy(meshBoat, mBoat, XMFLOAT3(0, 0.15f, 0));
		enemyBoat->GetTransform()->setScale(0.003f, 0.006f, 0.003f);
		int randCoord = rand() % 360;
		enemyBoat->GetTransform()->setPosition(cos(randCoord) * 10.0, 0, sin(randCoord) * 10.0);
		enemyBoat->GetTransform()->setRotate(0, 3.14159265358979323846/ -2.0,0);
		enemyBoat->setDirection();
		boats.push_back(enemyBoat);

	}

	


	*/
	//update camera
	camera->Update(deltaTime, this->hWnd);

	prevMouseClicked = GetAsyncKeyState(VK_LBUTTON);
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
	
	/*
	for(int i = 0; i < 2; i++)
	{

		if (entities[i]->GetMaterial()->GetNormalSRV().Get() == NULL)
		{
			SimpleVertexShader* vs = entities[i]->GetMaterial()->GetVertexShader();
			vs->SetFloat4("colorTint", entities[i]->GetMaterial()->GetColorTint());
			vs->SetMatrix4x4("world", entities[i]->GetTransform()->GetWorldMatrix());
			vs->SetMatrix4x4("view", camera->GetViewMatrix());
			vs->SetMatrix4x4("projection", camera->GetProjectionMatrix());

			vs->CopyAllBufferData();

			SimplePixelShader* ps = entities[i]->GetMaterial()->GetPixelShader();
			ps->SetFloat3("cameraPos", camera->getPosition());
			ps->SetData("light", &light, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor", ambient);
			ps->SetData("light2", &light2, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor2", ambient2);
			ps->SetData("light3", &light3, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor3", ambient3);
			ps->SetData("pointLight", &pointLight, sizeof(PointLight));
			ps->SetFloat3("pointAmbient", pointAmbient);
			ps->SetInt("lightType", 1);
			ps->SetFloat("matShine", entities[i]->GetMaterial()->Shininess());
			ps->CopyAllBufferData();

			ps->SetShaderResourceView("textureSRV", entities[i]->GetMaterial()->GetTextureSRV().Get());
			ps->SetSamplerState("basicSampler", entities[i]->GetMaterial()->GetSampler().Get());

			entities[i]->GetMaterial()->GetPixelShader()->SetShader();
			entities[i]->GetMaterial()->GetVertexShader()->SetShader();

		}
		else
		{
			SimpleVertexShader* vs = entities[i]->GetMaterial()->GetVertexShader();
			vs->SetFloat4("colorTint", entities[i]->GetMaterial()->GetColorTint());
			vs->SetMatrix4x4("world", entities[i]->GetTransform()->GetWorldMatrix());
			vs->SetMatrix4x4("view", camera->GetViewMatrix());
			vs->SetMatrix4x4("projection", camera->GetProjectionMatrix());

			vs->CopyAllBufferData();

			SimplePixelShader* ps = entities[i]->GetMaterial()->GetPixelShader();
			ps->SetFloat3("cameraPos", camera->getPosition());
			ps->SetData("light", &light, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor", ambient);
			ps->SetData("light2", &light2, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor2", ambient2);
			ps->SetData("light3", &light3, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor3", ambient3);
			ps->SetData("pointLight", &pointLight, sizeof(PointLight));
			ps->SetFloat3("pointAmbient", pointAmbient);
			ps->SetInt("lightType", 0);
			ps->SetFloat("matShine", entities[i]->GetMaterial()->Shininess());
			ps->CopyAllBufferData();

			ps->SetShaderResourceView("Albedo", entities[i]->GetMaterial()->GetTextureSRV().Get());
			ps->SetShaderResourceView("NormalMap", entities[i]->GetMaterial()->GetNormalSRV().Get());
			ps->SetShaderResourceView("RoughnessMap", entities[i]->GetMaterial()->GetRoughSRV().Get());
			ps->SetShaderResourceView("MetalNess", entities[i]->GetMaterial()->GetMetalSRV().Get());
			ps->SetSamplerState("basicSampler", entities[i]->GetMaterial()->GetSampler().Get());

			entities[i]->GetMaterial()->GetPixelShader()->SetShader();
			entities[i]->GetMaterial()->GetVertexShader()->SetShader();
		}

		

		// Set buffers in the input assembler
		//  - Do this ONCE PER OBJECT you're drawing, since each object might
		//    have different geometry.
		//  - for this demo, this step *could* simply be done once during Init(),
		//    but I'm doing it here because it's often done multiple times per frame
		//    in a larger application/game
		UINT stride = sizeof(Vertex);
		UINT offset = 0;


		context->IASetVertexBuffers(0, 1,entities[i]->GetMesh()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		context->IASetIndexBuffer(entities[i]->GetMesh()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
		context->DrawIndexed(entities[i]->GetMesh()->getIndecesies(), 0, 0);
	}

	//draw cannonballs on the screen 
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i]->isActive())
		{
			SimpleVertexShader* vs = balls[i]->GetMaterial()->GetVertexShader();
			vs->SetFloat4("colorTint", balls[i]->GetMaterial()->GetColorTint());
			vs->SetMatrix4x4("world", balls[i]->GetTransform()->GetWorldMatrix());
			vs->SetMatrix4x4("view", camera->GetViewMatrix());
			vs->SetMatrix4x4("projection", camera->GetProjectionMatrix());

			vs->CopyAllBufferData();

			SimplePixelShader* ps = balls[i]->GetMaterial()->GetPixelShader();
			ps->SetFloat3("cameraPos", camera->getPosition());
			ps->SetData("light", &light, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor", ambient);
			ps->SetData("light2", &light2, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor2", ambient2);
			ps->SetData("light3", &light3, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor3", ambient3);
			ps->SetData("pointLight", &pointLight, sizeof(PointLight));
			ps->SetFloat3("pointAmbient", pointAmbient);
			ps->SetInt("lightType", 0);
			ps->SetFloat("matShine", balls[i]->GetMaterial()->Shininess());
			ps->CopyAllBufferData();

			ps->SetShaderResourceView("Albedo", balls[i]->GetMaterial()->GetTextureSRV().Get());
			ps->SetShaderResourceView("NormalMap", balls[i]->GetMaterial()->GetNormalSRV().Get());
			ps->SetShaderResourceView("RoughnessMap", balls[i]->GetMaterial()->GetRoughSRV().Get());
			ps->SetShaderResourceView("MetalNess", balls[i]->GetMaterial()->GetMetalSRV().Get());
			ps->SetSamplerState("basicSampler", balls[i]->GetMaterial()->GetSampler().Get());

			balls[i]->GetMaterial()->GetPixelShader()->SetShader();
			balls[i]->GetMaterial()->GetVertexShader()->SetShader();

			UINT stride = sizeof(Vertex);
			UINT offset = 0;


			context->IASetVertexBuffers(0, 1, balls[i]->GetMesh()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
			context->IASetIndexBuffer(balls[i]->GetMesh()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
			context->DrawIndexed(balls[i]->GetMesh()->getIndecesies(), 0, 0);
		}
	}

	//draw boats on the screen
	for (int i = 0; i < boats.size(); i++)
	{
		if (boats[i]->isActive())
		{
			SimpleVertexShader* vs = boats[i]->GetMaterial()->GetVertexShader();
			vs->SetFloat4("colorTint", boats[i]->GetMaterial()->GetColorTint());
			vs->SetMatrix4x4("world", boats[i]->GetTransform()->lookAt(XMFLOAT3(0, 0.15f, 0)));
			vs->SetMatrix4x4("view", camera->GetViewMatrix());
			vs->SetMatrix4x4("projection", camera->GetProjectionMatrix());

			vs->CopyAllBufferData();

			SimplePixelShader* ps = boats[i]->GetMaterial()->GetPixelShader();
			ps->SetFloat3("cameraPos", camera->getPosition());
			ps->SetData("light", &light, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor", ambient);
			ps->SetData("light2", &light2, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor2", ambient2);
			ps->SetData("light3", &light3, sizeof(DirectionalLight));
			ps->SetFloat3("ambientColor3", ambient3);
			ps->SetData("pointLight", &pointLight, sizeof(PointLight));
			ps->SetFloat3("pointAmbient", pointAmbient);
			ps->SetInt("lightType", 0);
			ps->SetFloat("matShine", boats[i]->GetMaterial()->Shininess());
			ps->CopyAllBufferData();

			ps->SetShaderResourceView("Albedo", boats[i]->GetMaterial()->GetTextureSRV().Get());
			ps->SetShaderResourceView("NormalMap", boats[i]->GetMaterial()->GetNormalSRV().Get());
			ps->SetShaderResourceView("RoughnessMap", boats[i]->GetMaterial()->GetRoughSRV().Get());
			ps->SetShaderResourceView("MetalNess", boats[i]->GetMaterial()->GetMetalSRV().Get());
			ps->SetSamplerState("basicSampler", boats[i]->GetMaterial()->GetSampler().Get());

			boats[i]->GetMaterial()->GetPixelShader()->SetShader();
			boats[i]->GetMaterial()->GetVertexShader()->SetShader();

			UINT stride = sizeof(Vertex);
			UINT offset = 0;


			context->IASetVertexBuffers(0, 1, boats[i]->GetMesh()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
			context->IASetIndexBuffer(boats[i]->GetMesh()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
			context->DrawIndexed(boats[i]->GetMesh()->getIndecesies(), 0, 0);
		}
	}
	*/
	//sky->Draw(context, camera);
	// Present the back buffer to the user
//  - Puts the final frame we're drawing into the window so the user can see it
//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);

	// Due to the usage of a more sophisticated swap chain,
	// the render target must be re-bound after every call to Present()
	context->OMSetRenderTargets(1, backBufferRTV.GetAddressOf(), depthStencilView.Get());
}