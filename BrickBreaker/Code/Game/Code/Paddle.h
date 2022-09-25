#pragma once

#include "Entity.h"
#include "Engine/Graphics/Renderer.h"

class Paddle : public Entity
{
public:
    float m_Accelaration;
	Vec2 m_Velocity;
	ModelData m_ModelData;

	explicit Paddle(Game* owner);
	~Paddle();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
	virtual void DebugRender() override;
};