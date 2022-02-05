#include "stdafx.h"
#include "Device.h"
#include "Renders/Rect.h"

Rect* rect;
Rect* rect2;

void InitScene()
{
	rect = new Rect(L"../_Shaders/006_Rect.fx");
	rect->Position(200, 200);
	rect->Scale(100, 100);
	rect->Color(0, 1, 0);

	rect2 = new Rect
	(
		L"../_Shaders/006_Rect.fx",
		D3DXVECTOR2(500, 500),
		D3DXVECTOR2(100, 100),
		D3DXCOLOR(0, 0, 1, 1)
	);
	
}

void DestroyScene()
{
	SAFE_DELETE(rect);
	SAFE_DELETE(rect2);
}

D3DXMATRIX V, P;

void Update()
{

	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	rect->Update(V, P);
	rect2->Update(V, P);
	


}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		rect->Render();
		rect2->Render();
	
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
