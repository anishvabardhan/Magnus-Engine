#include "App.h"

#include "Game.h"
#include "GameCommon.h"
#include "Engine/Window/Window.h"
#include "Engine/Core/Time.h"
#include "Engine/Graphics/DIRECTX11/Renderer.h"
#include "Engine/Core/Logger.h"
#include "Engine/Input/InputSystem.h"
#include "Engine/Input/WinKeys.h"

#ifndef UNUSED
#define UNUSED(x) (void)x;
#endif

App* g_App = nullptr;

extern Window* g_Window;
extern InputSystem* g_InputSystem;

App::App()
{
}

App::~App()
{
}

void App::Startup()
{
	g_InputSystem = new InputSystem();
	g_InputSystem->Startup();

	g_Window = new Window();
	g_Window->Init("ProtoGame2D", CLIENT_DIMS);
	g_Window->SetInputSystem(g_InputSystem);

	LogStartup();
	
	g_Renderer = new Renderer();

	m_Time = new Time(60);

	m_Game = new Game();
}

void App::RunFrame()
{
	BeginFrame();
	Update(m_Time->GetTimeDelta());
	Render();
	EndFrame();
}

void App::BeginFrame()
{
	g_InputSystem->BeginFrame();

	g_Window->RunMessagePump();

	m_Time->Update();

	m_Game->BeginFrame();
}

void App::Update(float deltaseconds)
{
	g_InputSystem->Update(deltaseconds);
	UpdateFromInput();

	m_Game->Update(deltaseconds);

	g_InputSystem->EndFrame();
}

void App::Render()
{
	m_Game->Render();
}

void App::EndFrame()
{
	m_Game->EndFrame();

	m_IsQuitting = g_Window->IsAppQuiting();
}

void App::Shutdown()
{
	if(m_Game)
	{
		delete m_Game;
	    m_Game = nullptr;
	}
	
	//g_Renderer->ShutDown();
	//SAFE_DELETE_POINTER(g_Renderer)

	LogShutdown();

	g_Window->Destroy();
	SAFE_DELETE_POINTER(g_Window)

	g_InputSystem->ShutDown();
	SAFE_DELETE_POINTER(g_InputSystem)
}

void App::UpdateFromInput()
{
	if(g_InputSystem->WasKeyJustPressed(ESCAPE))
	{
		g_Window->AppQuitting();
	}

	if(g_InputSystem->WasKeyJustPressed(R))
	{
		const std::wstring title = L"Apex Engine 2.0";

		g_Window->SetTitle(title);
	}
}