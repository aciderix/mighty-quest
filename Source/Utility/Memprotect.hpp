/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 08-01-2018
    License: MIT
*/

#pragma once
#include "../Stdinclude.hpp"

namespace Memprotect
{
    #if defined(_WIN32)
    inline void Protectrange(void *Address, const size_t Length, unsigned long Oldprotection)
    {
        unsigned long Temp;
        VirtualProtect(Address, Length, Oldprotection, &Temp);
    }
    inline unsigned long Unprotectrange(void *Address, const size_t Length)
    {
        unsigned long Oldprotection;
        VirtualProtect(Address, Length, PAGE_EXECUTE_READWRITE, &Oldprotection);
        return Oldprotection;
    }
    #else
    inline void Protectrange(void *Address, const size_t Length, unsigned long Oldprotection)
    {
        int Pagesize = getpagesize();
        *(size_t *)&Address -= size_t(Address) % Pagesize;
        mprotect(Address, Pagesize, Oldprotection);
    }
    inline unsigned long Unprotectrange(void *Address, const size_t Length)
    {
        unsigned long Oldprotection = (PROT_READ | PROT_WRITE | PROT_EXEC);
        int Pagesize = getpagesize();
        *(size_t *)&Address -= size_t(Address) % Pagesize;
        mprotect(Address, Pagesize, PROT_READ | PROT_WRITE | PROT_EXEC);
        return Oldprotection;
    }
    #endif
}
