/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 31-01-2018
    License: MIT
*/

#include "../Stdinclude.hpp"

namespace Backend
{
    namespace Hero
    {
        struct Hero_t
        {
            Stat_t Stats;
            eHerotype Type;
            uint32_t Level;
            uint32_t TotalXP;
            std::vector<Spell_t> Spells;
            std::vector<Consumable_t> Consumables;
            std::vector<Attackregion_t> Knownregions;
            std::array<Equipment_t, (uint32_t)eItemslot::Count> Gear;

            MQEL_json Serialize()
            {
                if (Level == 0) return {};
                MQEL_json Object = MQEL_json::object();
                Object["HeroSpecContainerId"] = (uint32_t)Type;
                if(TotalXP) Object["XP"] = TotalXP;
                Object["Level"] = Level;
                for (auto &Item : Spells) Object["EquippedSpells"] += Item.Serialize();
                for (auto &Item : Consumables) Object["EquippedConsumables"] += Item.Serialize();
                Object["Stats"] = Stats.Serialize();
                for (auto &Item : Knownregions) Object["AttackRegions"] += Item.Serialize();
                return std::move(Object);
            }
        };
        std::array<Hero_t, (size_t)eHerotype::Count> Heroes{};
        Hero_t *Currenthero = &Heroes[0];

        template<> int Getheroclass() { return (int)Currenthero->Type; }
        template<> void Createhero(int Class)
        {
            Heroes[Class] = Hero_t();
            Currenthero = &Heroes[Class];
            Currenthero->Type = (eHerotype)Class;
            Currenthero->Level = 1;
        }
        template<> MQEL_json Serialize(int Class) { return Heroes[Class].Serialize(); }
        template<> void IncreaseXP(uint32_t XP, int Class) { Heroes[Class].TotalXP += XP; }
        template<> void Increaselevel(uint32_t Level, int Class) { Heroes[Class].Level += Level; }
        template<> void Equipspell(Spell_t Spell, int Class) { Heroes[Class].Spells.push_back(Spell); }
        template<> void Equipgear(int Slot, Equipment_t Item, int Class) { Heroes[Class].Gear[Slot] = Item; }

        void Savehero()
        {
            auto Object = MQEL_json::object();
            Object["Mage"] = Heroes[(size_t)eHerotype::Mage].Serialize();
            Object["Knight"] = Heroes[(size_t)eHerotype::Knight].Serialize();
            Object["Archer"] = Heroes[(size_t)eHerotype::Archer].Serialize();
            Object["Runaway"] = Heroes[(size_t)eHerotype::Runaway].Serialize();
            Object["Defaulthero"] = Currenthero->Type;
            std::string Plaintext = Object.dump(4);
            Package::Write("Heroes.json", Plaintext);
        }
        void Loadhero() { std::atexit(Savehero); }
        namespace { struct Startup { Startup() { Loadhero(); }; }; static Startup Loader{}; }
    }
}
