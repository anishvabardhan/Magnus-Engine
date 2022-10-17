#pragma once

#include "Engine/Core/CoreIncludes.h"

class InputSystem;

class Window
{
	InputSystem* m_InputSystem = nullptr;
public:
	Window();
	~Window();

	void Init(const String& appName, const long clientDims[4]);
	bool RunMessagePump();
	bool Destroy();

	void OnUpdate();

	inline void AppQuitting() { m_IsQuitting = true; }
	bool IsAppQuiting();

	inline void* GetHandle() const { return m_Hwnd; }
	inline InputSystem* GetInputSystem() const { return m_InputSystem; }
	inline void SetInputSystem(InputSystem* inputSystem) { m_InputSystem = inputSystem; }

	void SetTitle(const std::wstring& title);

	static Window* GetInstance();
protected:
	void* m_Hwnd = nullptr;
	bool m_IsQuitting = false;
public:
	bool GetMouse[256];
};

extern Window* g_Window;