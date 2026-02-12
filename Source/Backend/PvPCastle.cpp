/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 08-02-2018
    License: MIT
*/

#include "../Stdinclude.hpp"

namespace Backend
{
    namespace PvPCastle
    {
        std::unordered_map<uint64_t, MQEL_json::object_t> Castles;

        void Loadcastles()
        {
            auto Filelist = Package::Findfiles("Castle_");
            for (auto &Item : Filelist)
            {
                uint64_t CastleID{ 0 };
                std::sscanf(Item.c_str(), "Castle_%lld", &CastleID);
                if (CastleID == 0) continue;
                auto &Entry = Castles[CastleID];
                if (Entry.size() > 0) continue;
                try { Entry = MQEL_json::parse(Package::Read(Item).c_str()); }
                catch (std::exception &e) { Debugprint(va("%s (\"%s\"): %s", __FUNCTION__, Item.c_str(), e.what())); }
            }
        }

        MQEL_json Getcastle(uint64_t AccountID)
        {
            static bool Initialized = false;
            if(!Initialized) Createrecurringtask(Loadcastles, 5000);
            Initialized = true;
            return Castles[AccountID];
        }

        namespace { struct Startup { Startup() { Loadcastles(); }; }; static Startup Loader{}; }
    }
}
