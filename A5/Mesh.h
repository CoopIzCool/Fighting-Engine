#pragma once
#include "DXCore.h"
#include <DirectXMath.h>
#include <wrl/client.h>
#include "Vertex.h"

class Mesh
{
public:

	Mesh(Vertex* verts, int numVerts, unsigned int indicies[],
		int numIndicies, Microsoft::WRL::ComPtr<ID3D11Device> deviceObject);
	~Mesh();

	void GetBounds(Vertex* verts);
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetVertexBuffer();

	Microsoft::WRL::ComPtr<ID3D11Buffer> GetIndexBuffer();

	int getIndecesies();
	
	DirectX::XMFLOAT3 GetMinBounds();
	DirectX::XMFLOAT3 GetMaxBounds();

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	int indexes;
	DirectX::XMFLOAT3 minBounds = DirectX::XMFLOAT3(FLT_MIN, FLT_MIN, FLT_MIN);
	DirectX::XMFLOAT3 maxBounds = DirectX::XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
};

