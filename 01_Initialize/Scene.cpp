#include "Device.h"

void InitScene()
{
	MessageBox(Hwnd, L"InitScene", L"Test", MB_OK);
}

void DestroyScene()
{

}

void Update()
{

}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{


	}
	SwapChain->Present(0, 0);
}
