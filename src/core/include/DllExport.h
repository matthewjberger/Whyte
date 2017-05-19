#pragma once

#if defined(WHYTE_DLL) && defined(WHYTE_BUILD_DLL)
/*!
* WHYTE_DLL must be defined by applications that are linking against the DLL version of the Whyte library.
*/
#error "You may not have both WHYTE_DLL and WHYTE_BUILD_DLL defined"
#endif

/*!
* WHYTEAPI is used to declare public API classes / functions for export from the DLL / shared library / dynamic library
*/

// We are building Whyte as a Win32 DLL
#if defined(_WIN32) && defined(WHYTE_BUILD_DLL)
#define WHYTE_API __declspec(dllexport)

// We are calling Whyte as a Win32 DLL
#elif defined(_WIN32) && defined(WHYTE_DLL)
#define WHYTE_API __declspec(dllimport)

// We are building Whyte as a shared / dynamic library
#elif defined(__GNUC__) && defined(WHYTE_BUILD_DLL)
#define WHYTE_API __attribute__((visibility("default")))

// We are building or calling Whyte as a static library
#else
#define WHYTE_API

#endif