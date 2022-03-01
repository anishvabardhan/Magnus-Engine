#pragma once

#include "Engine/Core/EngineCommon.h"
#include "Engine/Maths/AABB2.h"


class Game
{
	AABB2 m_AABB2;
public:
	Game();
	~Game();

	void BeginFrame();
	void Update(float deltaseconds);
	void Render();
	void EndFrame();
};