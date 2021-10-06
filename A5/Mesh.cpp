#include "Mesh.h"

//constructor
Mesh::Mesh(Vertex* verts, int numVerts, unsigned int* indicies, int numIndicies, Microsoft::WRL::ComPtr<ID3D11Device> deviceObject)
{

	//description of buffer
	CD3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * numVerts;       
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	//struct for vertex data
	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = verts;

	//create buffer
	deviceObject->CreateBuffer(&vbd, &initialVertexData, vertexBuffer.GetAddressOf());

	indexes = numIndicies;

	//same thing for index
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(unsigned int) * numIndicies;	
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;	
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indicies;

	deviceObject->CreateBuffer(&ibd, &initialIndexData, indexBuffer.GetAddressOf());

	//check the bounds for collision boxes
	SetBounds(verts);
}


//destrctor
Mesh::~Mesh()
{
	
}



void Mesh::SetBounds(Vertex* verts)
{
	for (int i = 0; i < 4; i++)
	{
		if (verts[i].Position.x > maxBounds.x)
		{
			maxBounds.x = verts[i].Position.x;
		}
		else if (verts[i].Position.x < minBounds.x)
		{
			minBounds.x = verts[i].Position.x;
		}
		if (verts[i].Position.y > maxBounds.y)
		{
			maxBounds.y = verts[i].Position.y;
		}
		else if (verts[i].Position.y < minBounds.y)
		{
			minBounds.y = verts[i].Position.y;
		}
		if (verts[i].Position.z > maxBounds.z)
		{
			maxBounds.z = verts[i].Position.z;
		}
		else if (verts[i].Position.z < minBounds.z)
		{
			minBounds.z = verts[i].Position.z;
		}
	}
}

//properties
Microsoft::WRL::ComPtr<ID3D11Buffer> Mesh::GetVertexBuffer()
{
	return vertexBuffer;
}

Microsoft::WRL::ComPtr<ID3D11Buffer> Mesh::GetIndexBuffer()
{
	return indexBuffer;
}

int Mesh::getIndecesies()
{
	return indexes;
}

DirectX::XMFLOAT3 Mesh::GetMinBounds()
{
	return minBounds;
}

DirectX::XMFLOAT3 Mesh::GetMaxBounds()
{
	return maxBounds;
}
