/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 09-01-2018
    License: MIT
*/

#pragma once
#include <unordered_map>
#include "IServer.hpp"
#include <algorithm>
#include <vector>
#include <mutex>

struct IStreamserver : IServer
{
    std::unordered_map<size_t, std::vector<uint8_t>> Incomingstream;
    std::unordered_map<size_t, std::vector<uint8_t>> Outgoingstream;
    std::unordered_map<size_t, bool> Validconnection;
    std::mutex Threadguard;

    virtual void Send(const size_t Socket, const void *Databuffer, const uint32_t Datasize)
    {
        Threadguard.lock();
        auto Pointer = reinterpret_cast<const uint8_t *>(Databuffer);
        std::copy_n(Pointer, Datasize, std::back_inserter(Outgoingstream[Socket]));
        Threadguard.unlock();
    }
    virtual void Send(const size_t Socket, std::string Databuffer)
    {
        return Send(Socket, Databuffer.data(), uint32_t(Databuffer.size()));
    }
    virtual void onData(const size_t Socket, std::vector<uint8_t> &Stream) = 0;

    virtual void onDisconnect(const size_t Socket)
    {
        Threadguard.lock();
        Incomingstream[Socket].clear();
        Validconnection[Socket] = false;
        Threadguard.unlock();
    }
    virtual void onConnect(const size_t Socket, const uint16_t Port)
    {
        Threadguard.lock();
        Incomingstream[Socket].clear();
        Outgoingstream[Socket].clear();
        Validconnection[Socket] = true;
        Threadguard.unlock();
    }
    virtual bool onStreamread(const size_t Socket, void *Databuffer, uint32_t *Datasize)
    {
        if (0 == Outgoingstream[Socket].size()) return false;
        if (!Databuffer || !Datasize) return false;
        Threadguard.lock();
        if (0 != Outgoingstream[Socket].size())
        {
            *Datasize = std::min(*Datasize, uint32_t(Outgoingstream[Socket].size()));
            std::copy_n(Outgoingstream[Socket].begin(), *Datasize, reinterpret_cast<char *>(Databuffer));
            Outgoingstream[Socket].erase(Outgoingstream[Socket].begin(), Outgoingstream[Socket].begin() + *Datasize);
        }
        Threadguard.unlock();
        return true;
    }
    virtual bool onStreamwrite(const size_t Socket, const void *Databuffer, const uint32_t Datasize)
    {
        if (Validconnection[Socket] == false) return false;
        Threadguard.lock();
        auto Pointer = reinterpret_cast<const uint8_t *>(Databuffer);
        std::copy_n(Pointer, Datasize, std::back_inserter(Incomingstream[Socket]));
        onData(Socket, Incomingstream[Socket]);
        auto Discarded = Threadguard.try_lock();
        (void)Discarded;
        Threadguard.unlock();
        return true;
    }

    virtual bool onPacketread(Address_t &, void *, uint32_t *) { return false; }
    virtual bool onPacketwrite(const Address_t &, const void *, const uint32_t) { return false; }
};
