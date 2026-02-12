/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 09-01-2018
    License: MIT
*/

#pragma once
#include "IServer.hpp"
#include <algorithm>
#include <string>
#include <queue>
#include <mutex>

struct IDatagramserver : IServer
{
    std::queue<std::string> Packetqueue;
    Address_t Hostinformation{};
    std::mutex Threadguard;

    virtual void Send(std::string Databuffer)
    {
        Threadguard.lock();
        Packetqueue.push(Databuffer);
        Threadguard.unlock();
    }
    virtual void Send(const void *Databuffer, const uint32_t Datasize)
    {
        return Send({ reinterpret_cast<const char *>(Databuffer), Datasize });
    }
    virtual void onData(const std::string &Packet) = 0;

    virtual bool onPacketread(Address_t &Server, void *Databuffer, uint32_t *Datasize)
    {
        if (Packetqueue.empty()) return false;
        if (!Databuffer || !Datasize) return false;
        Threadguard.lock();
        if (!Packetqueue.empty())
        {
            auto Packet = Packetqueue.front();
            Packetqueue.pop();
            *Datasize = std::min(*Datasize, uint32_t(Packet.size()));
            std::copy_n(Packet.begin(), *Datasize, reinterpret_cast<char *>(Databuffer));
            std::memcpy(&Server, &Hostinformation, sizeof(Address_t));
        }
        Threadguard.unlock();
        return true;
    }
    virtual bool onPacketwrite(const Address_t &Server, const void *Databuffer, const uint32_t Datasize)
    {
        Threadguard.lock();
        std::memcpy(&Hostinformation, &Server, sizeof(Address_t));
        auto Pointer = reinterpret_cast<const char *>(Databuffer);
        auto Packet = std::string(Pointer, Datasize);
        onData(Packet);
        auto Discarded = Threadguard.try_lock();
        (void)Discarded;
        Threadguard.unlock();
        return true;
    }

    virtual void onDisconnect(const size_t) {}
    virtual void onConnect(const size_t, const uint16_t) {}
    virtual bool onStreamread(const size_t, void *, uint32_t *) { return false; }
    virtual bool onStreamwrite(const size_t, const void *, const uint32_t) { return false; }
};
