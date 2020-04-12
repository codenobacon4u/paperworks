#include "pwpch.h"
#include "Input.h"

#ifdef PW_PLATFORM_WINDOWS
#include "Platform/Windows/WinInput.h"
#endif

namespace Paperworks {
	Unique<Input> Input::s_Instance = Input::Create();

	Unique<Input> Paperworks::Input::Create()
	{
#ifdef PW_PLATFORM_WINDOWS
		return CreateUnique<WinInput>();
#else
		return nullptr;
#endif
	}
}