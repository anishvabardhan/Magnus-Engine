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

	g_Renderer->DrawMesh();
}

//--------------------------------------------------------------------------------------------------
// Ending the frame

void Game::EndFrame()
{
	g_Renderer->SwappingBuffers();
}

//--------------------------------------------------------------------------------------------------