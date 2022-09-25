#pragma once

#include "Game/Code/Map.h"
#include "Game/Code/Paddle.h"
#include "Game/Code/Ball.h"

class Camera;

class Game
{
	Camera* m_Camera = nullptr;
	Map m_Map;
public:
	Paddle m_Paddle;
	Ball m_Ball;
	bool m_DebugDraw = false;
	bool m_IsPaddleBallCollision = false;
public:
	Game();
	~Game();

	void BeginFrame();
	void Update(float deltaseconds);
	void Render();
	void EndFrame();
};