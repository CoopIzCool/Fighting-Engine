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
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetVertexBuffer();

	Microsoft::WRL::ComPtr<ID3D11Buffer> GetIndexBuffer();

	int getIndecesies();

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	int indexes;
};

