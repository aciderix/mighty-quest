/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 31-01-2018
    License: MIT
*/

#pragma once
#include "../Stdinclude.hpp"

namespace Backend
{
    namespace Quest
    {
        void Start(uint32_t QuestID);
        void Complete(uint32_t QuestID);
        std::vector<uint32_t> Getcompleted();
        void Update(uint32_t QuestID, uint32_t ActionID);
    }

    namespace Notification
    {
        std::vector<MQEL_json> Dequeuelocals();
        std::vector<MQEL_json> Dequeueglobals();
        void Enqueuelocal(MQEL_json Notification);
        void Enqueueglobal(MQEL_json Notification);
    }

    namespace Wallet
    {
        template<typename T> int32_t Getamount(T Type);
        template<typename T> uint32_t Getcapacity(T Type);
        template<typename T> void Setcapacity(T Type, uint32_t Max);
        template<typename T> void Updateamount(T Type, int32_t Delta);
        template<typename T> MQEL_json Serialize(T Type);
    }

    namespace Hero
    {
        template<typename C = int> C Getheroclass();
        template<typename C = int> void Createhero(C Class);
        template<typename C = int> MQEL_json Serialize(C Class = Getheroclass());
        template<typename C = int> void Increaselevel(uint32_t Level, C Class = Getheroclass());
        template<typename C = int> void Increasestats(Stat_t Delta, C Class = Getheroclass());
        template<typename C = int> void IncreaseXP(uint32_t XP, C Class = Getheroclass());
        template<typename T = int, typename C = int>
        void Equipgear(T Slot, Equipment_t Item, C Class = Getheroclass());
        template<typename C = int> void Equipspell(Spell_t Spell, C Class = Getheroclass());
    }

    namespace PvPCastle
    {
        MQEL_json Getcastle(uint64_t AccountID);
        constexpr uint64_t TutorialID1 = 0x2;
        constexpr uint64_t TutorialID2 = 0x3;
    }
}
