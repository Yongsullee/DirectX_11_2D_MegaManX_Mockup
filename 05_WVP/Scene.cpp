#include "stdafx.h"
#include "Device.h"

ID3D11Buffer* vertexBuffer;
ID3D11Buffer* vertexBuffer2;

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Color;
};

Vertex vertices[6];
Vertex vertices2[6];

D3DXCOLOR color = D3DXCOLOR(1, 0, 0, 1);

Shader* shader;

D3DXMATRIX W, W2;

D3DXMATRIX V, P;

void InitScene()
{

	shader = new Shader(L"../_Shaders/005_WVP.fx");

	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	vertices2[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices2[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices2[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices2[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices2[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices2[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	//vertices[0].Position = D3DXVECTOR3(-50.0f, -50.0f, 0.0f);
	//vertices[1].Position = D3DXVECTOR3(-50.0f, +50.0f, 0.0f);
	//vertices[2].Position = D3DXVECTOR3(+50.0f, -50.0f, 0.0f);
	//vertices[3].Position = D3DXVECTOR3(+50.0f, -50.0f, 0.0f);
	//vertices[4].Position = D3DXVECTOR3(-50.0f, +50.0f, 0.0f);
	//vertices[5].Position = D3DXVECTOR3(+50.0f, +50.0f, 0.0f);



	vertices[0].Color = D3DXVECTOR3(1, 0, 0);
	vertices[1].Color = D3DXVECTOR3(1, 0, 0);
	vertices[2].Color = D3DXVECTOR3(1, 0, 0);
	vertices[3].Color = D3DXVECTOR3(1, 0, 0);
	vertices[4].Color = D3DXVECTOR3(1, 0, 0);
	vertices[5].Color = D3DXVECTOR3(1, 0, 0);

	vertices2[0].Color = D3DXVECTOR3(0, 0, 1);
	vertices2[1].Color = D3DXVECTOR3(0, 0, 1);
	vertices2[2].Color = D3DXVECTOR3(0, 0, 1);
	vertices2[3].Color = D3DXVECTOR3(0, 0, 1);
	vertices2[4].Color = D3DXVECTOR3(0, 0, 1);
	vertices2[5].Color = D3DXVECTOR3(0, 0, 1);


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

	//Create Vertex Buffer2
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices2;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer2);
		assert(SUCCEEDED(hr));
	}
	
}

void DestroyScene()
{
	delete shader;

	vertexBuffer->Release();
	vertexBuffer2->Release();
}

D3DXVECTOR2 position = D3DXVECTOR2(100, 100);
D3DXVECTOR2 position2 = D3DXVECTOR2(100, 100);


void Update()
{
	//D3DXMatrixIdentity(&W);
	//D3DXMatrixIdentity(&V);
	//D3DXMatrixIdentity(&P);

	D3DXMATRIX S, T;

	D3DXMatrixScaling(&S, 100, 100, 1);
	D3DXMatrixTranslation(&T, position.x, position.y, 0);

	W = S * T;

	D3DXMatrixScaling(&S, 50, 50, 1);
	D3DXMatrixTranslation(&T, position2.x, position2.y, 0);

	W2 = S * T;


	//shader->AsVector("Color")->SetFloatVector(color);

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

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		//ImGui::ColorEdit4("Color", (float*)&color);

		ImGui::SliderFloat("X", &position.x, 100, Width - 100);
		ImGui::SliderFloat("Y", &position.y, 100, Height - 100);

		ImGui::SliderFloat("X2", &position2.x, 100, Width - 50);
		ImGui::SliderFloat("Y2", &position2.y, 100, Height - 50);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		shader->AsMatrix("World")->SetMatrix(W);
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		shader->Draw(0, 0, 6);

		shader->AsMatrix("World")->SetMatrix(W2);
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer2, &stride, &offset);
		shader->Draw(0, 0, 6);

	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
