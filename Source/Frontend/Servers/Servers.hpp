/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 09-01-2018
    License: MIT
*/

#pragma once
#include "../../Stdinclude.hpp"
#include "Interfaces/IServer.hpp"
#include "Interfaces/IStreamserver.hpp"
#include "Interfaces/IDatagramserver.hpp"
#include "Interfaces/ISSLServer.hpp"
#include "Interfaces/IHTTPServer.hpp"

struct Gameserver : IHTTPSServer
{
    virtual void onGET(const size_t Socket, HTTPRequest &Request) override;
    virtual void onPUT(const size_t Socket, HTTPRequest &Request) override;
    virtual void onPOST(const size_t Socket, HTTPRequest &Request) override;
    virtual void onCOPY(const size_t Socket, HTTPRequest &Request) override;
    virtual void onDELETE(const size_t Socket, HTTPRequest &Request) override;

    Gameserver()
    {
        if (!CreateSSLCert("Gameserver")) std::exit(3);
    }
};
