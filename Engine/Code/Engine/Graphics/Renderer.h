#pragma once

#if OPENGL_API
#include "OPENGL/Renderer.h"
#elif DX11_API
#include "DIRECTX11/Renderer.h"
#else
#error "NO_API_SELECTED"
#endif