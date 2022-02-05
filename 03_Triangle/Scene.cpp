#include "stdafx.h"
#include "Device.h"

ID3D11Buffer* vertexBuffer;
ID3D11InputLayout* inputLayout;
D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0}
	,{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA,0}
};

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Color;
};

Vertex vertices[6];

void InitScene()
{

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

	//Create InputLayout
	{
		HRESULT hr = Device->CreateInputLayout
		(
			layoutDesc, ARRAYSIZE(layoutDesc), VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(), &inputLayout
		);
		assert(SUCCEEDED(hr));
	}

	//int a = 10;

	//assert(a == 9);

}

void DestroyScene()
{
	inputLayout->Release();
	vertexBuffer->Release();
}

void Update()
{
	if (Key->Press('A') == true)
		vertices[0].Position.x -= 0.001f;
	else if (Key->Press('D') == true)
		vertices[0].Position.x += 0.001f;

	if (Key->Press('W') == true)
		vertices[0].Position.y += 0.001f;
	else if (Key->Press('S') == true)
		vertices[0].Position.y -= 0.001f;

	DeviceContext->UpdateSubresource
	(
		vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 6, 0
	);


}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DeviceContext->IASetInputLayout(inputLayout);

		DeviceContext->Draw(6, 0);

	}
	SwapChain->Present(0, 0);
}
