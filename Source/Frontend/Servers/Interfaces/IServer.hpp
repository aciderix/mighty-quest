/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 09-01-2018
    License: MIT
*/

#pragma once
#include <cstdint>

struct Address_t
{
    uint16_t Port;
    char Plainaddress[65];
};

struct IServer
{
    virtual bool onPacketread(Address_t &Server, void *Databuffer, uint32_t *Datasize) = 0;
    virtual bool onPacketwrite(const Address_t &Server, const void *Databuffer, const uint32_t Datasize) = 0;
    virtual void onDisconnect(const size_t Socket) = 0;
    virtual void onConnect(const size_t Socket, const uint16_t Port) = 0;
    virtual bool onStreamread(const size_t Socket, void *Databuffer, uint32_t *Datasize) = 0;
    virtual bool onStreamwrite(const size_t Socket, const void *Databuffer, const uint32_t Datasize) = 0;
};
