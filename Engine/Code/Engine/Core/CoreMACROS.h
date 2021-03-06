#pragma once

// Turn off all warnings for Third-Party libs at the start and turn it on at the end
#define THIRD_PARTY_INCLUDES_BEGIN #pragma warning(push, 0)
#define THIRD_PARTY_INCLUDES_END #pragma warning(pop)

//-----------------------------------------------------------------------------------

#define UNUSED(x) (void)x;
#define STATIC
#define INLINE
#define NOT_IN_USE
#define SAFE_DELETE_POINTER(ptr) if(nullptr != ptr) {delete ptr; ptr = nullptr;}