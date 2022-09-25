#include "Game.h"

#include "Engine/Core/EngineCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Camera.h"
//--------------------------------------------------------------------------------------------------

ModelData m;
float x = 0.0f;

Game::Game()
{
	Random::SetSeed();

	m_Camera = new Camera();
	m_Camera->SetPosition(Vec3(0.0f, 0.0f, -25.0f));
	m_Camera->SetPersp(90.0f, MAGNUS_WINDOW_DIMS[1] / MAGNUS_WINDOW_DIMS[3], 0.1f, 100.0f);
}

Game::~Game() 
{
}

//--------------------------------------------------------------------------------------------------
// Begin Frame function

void Game::BeginFrame()
{
}

//--------------------------------------------------------------------------------------------------
// Updates happening every frame

void Game::Update(float deltaseconds)
{
	UNUSED(deltaseconds)
		
	x += deltaseconds;
	m.m_Model =  Mat4::Translation(Vec3(0.0f, 0.0f, 25.0f)) * Mat4::RotationY3D(x) * Mat4::RotationX3D(0) * Mat4::RotationZ3D(0);

	m_Camera->Update(deltaseconds);
}

//--------------------------------------------------------------------------------------------------
// Rendering the frame

void Game::Render()
{
	g_Renderer->ClearScreen(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	g_Renderer->DrawCube(Vec3(0.0f, 0.0f, 0.0f), Vec3(2.0f, 2.0f, 2.0f), Color::BLUE, m);
}

//--------------------------------------------------------------------------------------------------
// Ending the frame

void Game::EndFrame()
{
	g_Renderer->SwappingBuffers();
}

//--------------------------------------------------------------------------------------------------