/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 09-01-2018
    License: MIT
    Notes: SSL over TCP parsing - requires OpenSSL
*/

#pragma once
#if __has_include(<openssl\\ssl.h>)
#include "../../Stdinclude.hpp"
#include <openssl\\bio.h>
#include <openssl\\ssl.h>
#include <openssl\\err.h>

struct ISSLServer : IStreamserver
{
    std::unordered_map<size_t, SSL_CTX *> Context;
    std::unordered_map<size_t, BIO *> Write_BIO;
    std::unordered_map<size_t, BIO *> Read_BIO;
    std::unordered_map<size_t, SSL *> State;
    X509 *SSLCertificate;
    EVP_PKEY *SSLKey;

    virtual void Syncbuffers(const size_t Socket);
    virtual bool CreateSSLCert(std::string_view Hostname);
    virtual void onStreamdecrypted(const size_t Socket, std::vector<uint8_t> &Stream) = 0;
    virtual void Send(const size_t Socket, const void *Databuffer, const uint32_t Datasize);
    virtual void Send(const size_t Socket, std::string &Databuffer);
    virtual void onData(const size_t Socket, std::vector<uint8_t> &Stream);
    virtual void onDisconnect(const size_t Socket);
    virtual void onConnect(const size_t Socket, const uint16_t Port);
};
#endif
