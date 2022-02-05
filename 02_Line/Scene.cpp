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


void InitScene()
{
	//Vertex vertices[2];
	//vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	//vertices[1].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	Vertex vertices[4];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);

	vertices[0].Color = D3DXVECTOR3(1, 0, 0);
	vertices[1].Color = D3DXVECTOR3(0, 0, 1);
	vertices[2].Color = D3DXVECTOR3(0, 1, 0);
	vertices[3].Color = D3DXVECTOR3(1, 0, 1);


	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 4;
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

}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		//DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		DeviceContext->IASetInputLayout(inputLayout);

		DeviceContext->Draw(4, 0);

	}
	SwapChain->Present(0, 0);
}
