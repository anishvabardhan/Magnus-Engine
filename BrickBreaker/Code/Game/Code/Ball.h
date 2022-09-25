#pragma once

#include "Entity.h"
#include "Engine/Graphics/Renderer.h"

class Ball : public Entity
{
public:
	ModelData m_ModelData;
	Vec2 m_Velocity;
	float m_Radius;
	bool m_HasLaunched = false;

	Ball(Game* owner);
	~Ball();

	virtual void Update(float deltaseconds) override;
	virtual void Render() override;
	virtual void DebugRender() override;

	void Translate(const Vec2& translate);
};