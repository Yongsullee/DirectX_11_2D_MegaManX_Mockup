#include "stdafx.h"
#include "Device.h"

ID3D11Buffer* vertexBuffer;

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Color;
};

Vertex vertices[6];

D3DXCOLOR color = D3DXCOLOR(1, 0, 0, 1);

Shader* shader;

void InitScene()
{

	shader = new Shader(L"../_Shaders/004_Effect.fx");

	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);


	vertices[0].Color = D3DXVECTOR3(1, 0, 0);
	vertices[1].Color = D3DXVECTOR3(1, 0, 0);
	vertices[2].Color = D3DXVECTOR3(1, 0, 0);
	vertices[3].Color = D3DXVECTOR3(1, 0, 0);
	vertices[4].Color = D3DXVECTOR3(1, 0, 0);
	vertices[5].Color = D3DXVECTOR3(1, 0, 0);


	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	
}

void DestroyScene()
{
	delete shader;

	vertexBuffer->Release();
}

void Update()
{
	
	shader->AsVector("Color")->SetFloatVector(color);
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		ImGui::ColorEdit4("Color", (float*)&color);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
		shader->Draw(0, 0, 6);

	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
