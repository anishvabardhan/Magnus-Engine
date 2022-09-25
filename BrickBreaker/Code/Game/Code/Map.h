#pragma once

#include "Brick.h"
#include "Entity.h"
#include "Engine/Graphics/Renderer.h"

class Map : public Entity
{
	Brick* m_Bricks[BB_NUM_OF_ROWS][BB_NUM_OF_COLS];
    ModelData m_ModelData;
public:
	bool m_IsBrickBallCollided[BB_NUM_OF_ROWS][BB_NUM_OF_COLS];
public:
	Map(Game* owner);
	~Map();

	void Update(float deltaseconds);
	void Render();

	void BallBrickCollision();
	void BallPaddleCollision();
};
