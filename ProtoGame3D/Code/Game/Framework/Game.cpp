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

const Mat4 g_Camera = Mat4::Orthographic(APEX_WINDOW_DIMS[0], APEX_WINDOW_DIMS[1], APEX_WINDOW_DIMS[2], APEX_WINDOW_DIMS[3], -2.0f, 2.0f);

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
	g_Renderer->ClearColor(Vec4(1.0f, 0.0f, 0.0f, 1.0f));

	//AABB2 aabb2(Vec2(400.0f, 400.0f), Vec2(600.0f, 600.0f));
	//
	//g_Renderer->SetCameraUniform(g_Camera);
	//
	//g_Renderer->BindTexture();
	//
	//g_Renderer->SetModelTranslation();
	//g_Renderer->DrawAABB2(aabb2, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	//
	//Vec2 temp = aabb2.GetNearestPoint(g_InputSystem->GetMousePosition());
	//Vec2 start = temp;
	//Vec2 end = g_InputSystem->GetMousePosition();
	//
	//g_Renderer->SetModelTranslation();
	//g_Renderer->DrawArrow(start, end, 5.0f, Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//
	//g_Renderer->SetModelTranslation();
	//g_Renderer->DrawDisc(g_InputSystem->GetMousePosition(), 10.0f, Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	//
	//if(Disc_AABB2Collision(end, 10.0f, aabb2))
	//{
	//    g_Renderer->SetModelTranslation();
	//    g_Renderer->DrawDisc(Vec2(800.0f, 800.0f), 20.0f, Vec4(0.5f, 0.5f, 0.5f, 1.0f));
	//}
}

//--------------------------------------------------------------------------------------------------
// Ending the frame

void Game::EndFrame()
{
	g_Renderer->SwappingBuffers();
}

//--------------------------------------------------------------------------------------------------