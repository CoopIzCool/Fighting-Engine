#pragma once
#include "DXCore.h"
#include <DirectXMath.h>
#include <wrl/client.h>
#include "Vertex.h"

class Mesh
{
public:

	Mesh(Vertex* verts, int numVerts, unsigned int* indicies,
		int numIndicies, Microsoft::WRL::ComPtr<ID3D11Device> deviceObject);
	Mesh(const char* fileName, Microsoft::WRL::ComPtr<ID3D11Device> deviceObject);
	~Mesh();
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetVertexBuffer();

	Microsoft::WRL::ComPtr<ID3D11Buffer> GetIndexBuffer();

	int getIndecesies();
	DirectX::XMFLOAT3 getMinBound();
	DirectX::XMFLOAT3 getMaxBound();

	void createBuffer(Vertex* verts, int numVerts, unsigned int* indicies, int numIndicies, Microsoft::WRL::ComPtr<ID3D11Device> deviceObject);
	void CalculateTangents(Vertex* verts, int numVerts, unsigned int* indices, int numIndices);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	DirectX::XMFLOAT3 minBound = DirectX::XMFLOAT3(0,0,0);
	DirectX::XMFLOAT3 maxBound = DirectX::XMFLOAT3(0,0,0);
	int indexes;
};

