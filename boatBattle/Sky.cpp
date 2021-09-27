#include "Sky.h"

using namespace DirectX;
Sky::Sky(Mesh* drawnMesh, Microsoft::WRL::ComPtr<ID3D11SamplerState> sample, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, SimplePixelShader* pixel,
	SimpleVertexShader* vertex, Microsoft::WRL::ComPtr<ID3D11Device> deviceObject)
{
	mesh = drawnMesh;
	sampler = sample;
	textureSRV = texture;
	pixelShader = pixel;
	vertexShader = vertex;

	D3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_FRONT;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.DepthClipEnable = true;
	deviceObject->CreateRasterizerState(&rastDesc, rasterizer.GetAddressOf());

	CD3D11_DEPTH_STENCIL_DESC depthDesc = {};
	depthDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthDesc.DepthEnable = true;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	deviceObject->CreateDepthStencilState(&depthDesc, depth.GetAddressOf());
}

void Sky::Draw(Microsoft::WRL::ComPtr <ID3D11DeviceContext> context,Camera* cam)
{
	context->RSSetState(rasterizer.Get());
	context->OMSetDepthStencilState(depth.Get(), 0);

	pixelShader->SetShader();
	vertexShader->SetShader();

	vertexShader->SetMatrix4x4("view", cam->GetViewMatrix());
	vertexShader->SetMatrix4x4("projection", cam->GetProjectionMatrix());
	vertexShader->CopyAllBufferData();

	pixelShader->SetShaderResourceView("textureCube", textureSRV.Get());
	pixelShader->SetSamplerState("basicSampler", sampler.Get());

	UINT stride = sizeof(Vertex);
	UINT offset = 0;


	context->IASetVertexBuffers(0, 1, mesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(mesh->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(mesh->getIndecesies(), 0, 0);

	context->RSSetState(0);
	context->OMSetDepthStencilState(0, 0);
}
