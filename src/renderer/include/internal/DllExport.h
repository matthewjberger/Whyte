#pragma once

#if defined(WHYRE_DLL) && defined(WHYRE_BUILD_DLL)
/*!
* WHYRE_DLL must be defined by applications that are linking against the DLL version of the Whyte library.
*/
#error "You may not have both WHYRE_DLL and WHYRE_BUILD_DLL defined"
#endif

/*!
* WHYREAPI is used to declare public API classes / functions for export from the DLL / shared library / dynamic library
*/

// We are building Whyte as a Win32 DLL
#if defined(_WIN32) && defined(WHYRE_BUILD_DLL)
#define WHYRE_API __declspec(dllexport)

// We are calling Whyte as a Win32 DLL
#elif defined(_WIN32) && defined(WHYRE_DLL)
#define WHYRE_API __declspec(dllimport)

// We are building Whyte as a shared / dynamic library
#elif defined(__GNUC__) && defined(WHYRE_BUILD_DLL)
#define WHYRE_API __attribute__((visibility("default")))

// We are building or calling Whyte as a static library
#else
#define WHYRE_API

#endif