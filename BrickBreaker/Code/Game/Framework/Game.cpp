#include "Game.h"

#include "Engine/Core/EngineCommon.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Camera.h"
//--------------------------------------------------------------------------------------------------

Game::Game()
	:m_Paddle(Paddle(this)),
     m_Map(Map(this)),
     m_Ball(Ball(this))
{
	Random::SetSeed();

	m_Camera = new Camera();
	m_Camera->SetPosition(Vec3(0.0f, 0.0f, -25.0f));
	m_Camera->SetOrtho(MAGNUS_WINDOW_DIMS[0], MAGNUS_WINDOW_DIMS[1], MAGNUS_WINDOW_DIMS[2], MAGNUS_WINDOW_DIMS[3], -2.0f, 2.0f);
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
		
	m_Camera->Update(deltaseconds);

	m_Paddle.Update(deltaseconds);
	m_Map.Update(deltaseconds);
	m_Ball.Update(deltaseconds);
}

//--------------------------------------------------------------------------------------------------
// Rendering the frame

void Game::Render()
{
	g_Renderer->ClearScreen(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	m_Map.Render();
	m_Ball.Render();
	m_Paddle.Render();
}

//--------------------------------------------------------------------------------------------------
// Ending the frame

void Game::EndFrame()
{
	g_Renderer->SwappingBuffers();
}

//--------------------------------------------------------------------------------------------------