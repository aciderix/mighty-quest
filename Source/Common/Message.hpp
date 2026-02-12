/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 14-01-2018
    License: MIT
*/

#pragma once
#include "../Stdinclude.hpp"

template<class K, class V, class dummy_compare, class A = std::allocator<K>>
using MQEL_map = nlohmann::fifo_map<K, V, nlohmann::fifo_map_compare<K>, A>;
using MQEL_json = nlohmann::basic_json<MQEL_map>;

class Message_t
{
    MQEL_json Internalstate;

public:
    template<typename T>
    typename std::enable_if<!std::is_same<T, const char *>::value, T>::type
    Get(std::string Property, T Fallback)
    {
        if (Internalstate[Property].is_null() || Internalstate[Property].empty())
            return Fallback;
        return Internalstate[Property];
    }
    std::string Get(std::string Property, std::string Fallback)
    {
        if (Internalstate[Property].is_null() || Internalstate[Property].empty())
            return Fallback;
        return Internalstate[Property];
    }
    template<typename T> void Set(std::string Property, T Value)
    {
        Internalstate[Property] = Value;
    }

    MQEL_json toJSON() { return Internalstate; }
    std::string toString() { return Internalstate.dump(4); }

    Message_t() = default;
    Message_t(const MQEL_json Parent) : Internalstate(Parent) {};
    Message_t(const MQEL_json &&Parent) : Internalstate(Parent) {};
    Message_t(const std::string Plaintext) : Internalstate(MQEL_json::parse(Plaintext)) {};
    Message_t(const std::string &&Plaintext) : Internalstate(MQEL_json::parse(Plaintext)) {};
};

inline void from_json(const MQEL_json &JSON, Message_t &Message) { Message = { JSON }; }
inline void to_json(MQEL_json &JSON, Message_t &Message) { JSON = Message.toJSON(); }
using Response_t = Message_t;
using Request_t = Message_t;
