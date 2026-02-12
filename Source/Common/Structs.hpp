/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 31-01-2018
    License: MIT
*/

#pragma once
#include "Enumerations.hpp"
#include "../Stdinclude.hpp"

struct Stat_t
{
    uint32_t Creatureskilled;
    uint32_t Castleslooted;
    uint32_t Timesplayed;

    MQEL_json Serialize()
    {
        MQEL_json Object = MQEL_json::object();
        if (Creatureskilled) Object["TotalCreaturesKilled"] = Creatureskilled;
        if (Castleslooted) Object["TotalCastlesLooted"] = Castleslooted;
        if (Timesplayed) Object["TimePlayed"] = Timesplayed;
        return Object;
    }
};

struct Spell_t
{
    uint32_t ID;
    uint32_t Slot;

    MQEL_json Serialize()
    {
        MQEL_json Object = MQEL_json::object();
        if (Slot) Object["SlotIndex"] = Slot;
        Object["SpellSpecContainerId"] = ID;
        return Object;
    }
};

struct Effect_t
{
    uint32_t ID;
    uint32_t Level;

    MQEL_json Serialize()
    {
        MQEL_json Object = MQEL_json::object();
        Object["Id"] = ID;
        Object["Level"] = Level;
        return Object;
    }
};

struct Equipment_t
{
    uint32_t ID;
    uint32_t Dye;
    bool Branded;
    bool Sellable;
    uint32_t Level;
    uint32_t Archetype;
    std::string Itemtype;
    std::vector<double> Modifiers;
    std::vector<Effect_t> Effects;

    MQEL_json Serialize()
    {
        MQEL_json Object = MQEL_json::object();
        Object["Type"] = Itemtype;
        Object["ItemLevel"] = Level;
        Object["ArchetypeId"] = Archetype;
        Object["PrimaryStatsModifiers"] = Modifiers;
        for (auto &Item : Effects) Object["Effects"] += Item.Serialize();
        if (Sellable) Object["IsSellable"] = Sellable;
        if (Branded) Object["IsBranded"] = Branded;
        Object["TemplateId"] = ID;
        Object["DyeTemplateId"] = Dye;
        return Object;
    }
};

struct Consumable_t
{
    uint32_t ID;
    MQEL_json Serialize()
    {
        MQEL_json Object = MQEL_json::object();
        Object["TemplateId"] = ID;
        return Object;
    }
};

struct Attackregion_t
{
    uint32_t ID;
    eRegionstatus Status;

    MQEL_json Serialize()
    {
        MQEL_json Object = MQEL_json::object();
        Object["AttackRegionId"] = ID;
        Object["Status"] = (uint32_t)Status;
        return Object;
    }
};
