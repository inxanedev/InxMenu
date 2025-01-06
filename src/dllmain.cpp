#include <Windows.h>
#include "../ext/ImGui DirectX 11 Kiero Hook/includes.h"
#include "gui/gui.h"
#include "patching/PatternScanner.h"
#include <iostream>
#include "../ext/safetyhook.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

ProcessInfo info;
GUI gui(info);

bool is_inactive = false;

LRESULT __stdcall WndProc(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_KEYUP && wParam == VK_END) {
		gui.m_is_open = !gui.m_is_open;
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDrawCursor = gui.m_is_open;
		io.WantCaptureMouse = gui.m_is_open;
	}

	if (gui.m_is_open) {
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	}

	if (gui.m_is_open && !is_inactive) {
		CallWindowProc(reinterpret_cast<WNDPROC>(oWndProc), hWnd, WM_ACTIVATE, WA_INACTIVE, 0);
		is_inactive = true;
	}
	else if (!gui.m_is_open && is_inactive) {
		CallWindowProc(reinterpret_cast<WNDPROC>(oWndProc), hWnd, WM_ACTIVATE, WA_ACTIVE, 0);
		is_inactive = false;
	}

	return gui.m_is_open ? gui.m_is_open : CallWindowProc(reinterpret_cast<WNDPROC>(oWndProc), hWnd, msg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (gui.m_is_open) gui.Render();

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	AllocConsole();
	FILE* dummy;
	freopen_s(&dummy, "CONOUT$", "w", stdout);

	ProcessInfo info;
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
    }

	if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		kiero::shutdown();
	}
    
    return true;
}

