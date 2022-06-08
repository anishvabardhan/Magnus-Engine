#include "Game.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Input/InputSystem.h"

//--------------------------------------------------------------------------------------------------

Game::Game()
{
	Random::SetSeed();
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
}

//--------------------------------------------------------------------------------------------------
// Rendering the frame

void Game::Render()
{
	g_Renderer->ClearScreen(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	g_Renderer->DrawAABB2(AABB2(Vec2(-2.5f, -2.5f), Vec2(2.5f, 2.5f)), Color::RED);
}

//--------------------------------------------------------------------------------------------------
// Ending the frame

void Game::EndFrame()
{
	g_Renderer->SwappingBuffers();
}

//--------------------------------------------------------------------------------------------------