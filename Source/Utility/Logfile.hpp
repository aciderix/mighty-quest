/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 08-01-2018
    License: MIT
*/

#pragma once
#include "Variadicstring.hpp"
#include "../Stdinclude.hpp"

namespace Internal
{
    #if !defined(MODULENAME)
        #define MODULENAME "Invalid"
    #endif

    constexpr const char *Filepath = "./Plugins/Logs/" MODULENAME ".log";
    static std::mutex Threadguard;
}

inline void Logprint(std::string_view Message)
{
    Internal::Threadguard.lock();
    {
        auto Filehandle = std::fopen(Internal::Filepath, "a");
        if (Filehandle)
        {
            std::fputs(Message.data(), Filehandle);
            std::fputs("\n", Filehandle);
            std::fclose(Filehandle);
        }
    }
    Internal::Threadguard.unlock();

    #if !defined(NDEBUG)
        std::fputs(Message.data(), stderr);
        std::fputs("\n", stderr);
    #endif
}

inline void Logformatted(std::string_view Message, char Prefix)
{
    auto Now = std::time(NULL);
    char Buffer[80]{};
    std::strftime(Buffer, 80, "%H:%M:%S", std::localtime(&Now));
    Logprint(va("[%c][%-8s] %*s", Prefix, Buffer, static_cast<int>(Message.size()), Message.data()));
}

inline void Clearlog()
{
    std::remove(Internal::Filepath);
    Logformatted(MODULENAME " - Starting up..", 'I');
}
