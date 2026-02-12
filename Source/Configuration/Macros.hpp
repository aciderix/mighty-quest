/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 08-01-2018
    License: MIT
*/

#pragma once

#if defined(NDEBUG)
    #define Printfunction()
    #define Debugprint(string)
#else
    #define Printfunction() Logformatted(__FUNCTION__, 'T')
    #define Debugprint(string) Logformatted(string, 'D')
#endif

#define Infoprint(string) Logformatted(string, 'I')
#define vaprint(format, ...) Logprint(va(format, __VA_ARGS__))

#if defined(_WIN32)
    #define likely(x)       x
    #define unlikely(x)     x
#else
    #define likely(x)       __builtin_expect(!!(x), 1)
    #define unlikely(x)     __builtin_expect(!!(x), 0)
#endif

#define Findpattern(Segment, String) Pattern::_Findpattern(Segment, Pattern::Stringtopattern(String), Pattern::Stringtomask(String))
