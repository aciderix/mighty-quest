/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 08-01-2018
    License: MIT
*/

#include "Stdinclude.hpp"

int Verifycert(int Result, void *Context) { return 1; }
long Getresult(void *Context) { return 0; }

extern "C" EXPORT_ATTR IServer *Createserver(const char *Hostname)
{
    if (std::strstr(Hostname, "Gameserver"))
    {
        auto Address = Findpattern(Pattern::Textsegment, "8B 44 24 04 8B 4C 24 08 8B 54 24 0C 89 88 C0 00 00 00 89 90 E8 00 00 00 C3");
        if (Address) Hooking::Stomphook().Installhook((void *)Address, (void *)Verifycert);
        Address = Findpattern(Pattern::Textsegment, "8B 44 24 04 8B 80 EC 00 00 00 C3");
        if (Address) Hooking::Stomphook().Installhook((void *)Address, (void *)Getresult);
        return new Gameserver();
    }
    return nullptr;
}

#if defined _WIN32
BOOLEAN WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
{
    switch (nReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            if (!std::strstr(GetCommandLineA(), "-server_url"))
            {
                std::string Errormessage = "Please restart with:\n\n";
                Errormessage += "MightyQuest.exe ";
                Errormessage += "-server_url https://Gameserver ";
                Errormessage += "-environmentName mqel-live\n";
                MessageBoxA(0, Errormessage.c_str(), "Missing arguments", 0);
                std::exit(3);
            }
            DisableThreadLibraryCalls(hDllHandle);
            Clearlog();
        }
    }
    return TRUE;
}
#else
__attribute__((constructor)) void DllMain() { Clearlog(); }
#endif
