#pragma once

#ifdef PW_PLATFORM_WINDOWS
	#ifdef PW_BUILD_DLL
		#define PAPERWORKS_API __declspec(dllexport)
	#else
		#define PAPERWORKS_API __declspec(dllimport) 
	#endif // PW_BUILD_DLL
#else
	#error Paperworks only supports Windows!
#endif // PW_PLATFORM_WINDOWS
