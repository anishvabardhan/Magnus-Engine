#include "Game.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderDefinition.h"
#include "Engine/Window/Window.h"
#include "Engine/Core/EngineCommon.h"

#include "Engine/Input/InputSystem.h"
#include "Engine/Maths/MathUtils.h"

// Declaring Engine Systems

extern InputSystem* g_InputSystem;
extern Window* g_Window;

//--------------------------------------------------------------------------------------------------
// Creating a Camera

//const Mat4 g_Camera = Mat4::Orthographic(MAGNUS_WINDOW_DIMS[0], MAGNUS_WINDOW_DIMS[1], MAGNUS_WINDOW_DIMS[2], MAGNUS_WINDOW_DIMS[3], -2.0f, 2.0f);

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
	g_Renderer->ClearColor(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	Vec2 start = Vec2(-0.5f, -0.5f);
	Vec2 end = Vec2(0.5f, 0.5f);
	
	Vec2 start2 = Vec2(0.5f, -0.5f);
	Vec2 end2 = Vec2(-0.5f, 0.5f);

	g_Renderer->DrawDisc(Vec2(0.0f, 0.0f), 0.05f, Color::RED);
	//g_Renderer->DrawHollowAABB2(AABB2(Vec2(-0.6f,-0.6f), Vec2( 0.6f, 0.6f)), 0.05f, Color::RED);
	//g_Renderer->DrawAABB2(AABB2(Vec2(-0.5f,-0.5f), Vec2( 0.5f, 0.5f)), Color::GREEN);
	//g_Renderer->DrawLine(start, end, 0.01f, Color::BLUE);
	//g_Renderer->DrawArrow(start2, end2, 0.01f, Color::YELLOW);
}

//--------------------------------------------------------------------------------------------------
// Ending the frame

void Game::EndFrame()
{
	g_Renderer->SwappingBuffers();
}

//--------------------------------------------------------------------------------------------------