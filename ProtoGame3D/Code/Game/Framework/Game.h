#pragma once

class Camera;

class Game
{
	Camera* m_Camera = nullptr;
public:
	Game();
	~Game();

	void BeginFrame();
	void Update(float deltaseconds);
	void Render();
	void EndFrame();
};