#include "stdafx.h"
#include "Device.h"

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR2 Uv;
};

ID3D11Buffer* vertexBuffer;

Shader* shader;
ID3D11ShaderResourceView* srv;


void InitScene()
{
	Vertex vertices[6];

	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = D3DXVECTOR2(0, 1);
	vertices[1].Uv = D3DXVECTOR2(0, 0);
	vertices[2].Uv = D3DXVECTOR2(1, 1);
	vertices[3].Uv = D3DXVECTOR2(1, 1);
	vertices[4].Uv = D3DXVECTOR2(0, 0);
	vertices[5].Uv = D3DXVECTOR2(1, 0);


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
	
	//Create SRV
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			Device, L"../_Textures/Mario/Single.png", NULL, NULL, &srv, NULL
		);
		assert(SUCCEEDED(hr));
	}

	shader = new Shader(L"../_Shaders/007_Texture.fx");
	shader->AsShaderResource("Map")->SetResource(srv);

}

void DestroyScene()
{
	SAFE_DELETE(shader);

	SAFE_RELEASE(srv);
	SAFE_RELEASE(vertexBuffer);

}

D3DXMATRIX V, P;

void Update()
{
	D3DXMATRIX  W, S, T;

	D3DXMatrixScaling(&S, 100, 100, 1);
	D3DXMatrixTranslation(&T, 200, 200, 0);

	W = S * T;

	shader->AsMatrix("World")->SetMatrix(W);
	
	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
}

int pass = 0;

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		ImGui::SliderInt("Pass", &pass, 0, 1);
		shader->Draw(0, pass, 6);
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
