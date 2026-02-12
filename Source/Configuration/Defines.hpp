/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 08-01-2018
    License: MIT
*/

#pragma once
#pragma warning(disable: 4100 4189 4307)

#define MODULENAME "MQELOnline"
#define MODULEEXTENSION "Localnet"

#if !defined(_DEBUG) && !defined(NDEBUG)
#define NDEBUG
#endif

#if defined(_MSC_VER)
    #define EXPORT_ATTR __declspec(dllexport)
    #define IMPORT_ATTR __declspec(dllimport)
#elif defined(__GNUC__)
    #define EXPORT_ATTR __attribute__((visibility("default")))
    #define IMPORT_ATTR
#else
    #define EXPORT_ATTR
    #define IMPORT_ATTR
    #error Compiling for unknown platform.
#endif

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
    #define ENVIRONMENT64
#endif

#if defined(_WIN32)
    #define _CRT_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS
#endif
