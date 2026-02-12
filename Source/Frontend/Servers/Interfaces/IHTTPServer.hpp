/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 09-01-2018
    License: MIT
    Notes: HTTP over TCP parsing
*/

#include "../../Stdinclude.hpp"
#include "../../Utility/Thirdparty/http_parser.h"

struct HTTPHeader { std::string Field; std::string Value; };
struct HTTPRequest
{
    bool Parsed;
    std::string URL;
    std::string Method;
    std::vector<HTTPHeader> Headers;
    std::string Body;
};

struct IHTTPServer : IStreamserver
{
    std::unordered_map<size_t, http_parser> Parser;
    std::unordered_map<size_t, HTTPRequest> Parsedrequest;
    std::unordered_map<size_t, http_parser_settings> Parsersettings;

    virtual void onGET(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onPUT(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onPOST(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onCOPY(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onDELETE(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onData(const size_t Socket, std::vector<uint8_t> &Stream);
};

#if __has_include(<openssl\\ssl.h>)
struct IHTTPSServer : ISSLServer
{
    std::unordered_map<size_t, http_parser> Parser;
    std::unordered_map<size_t, HTTPRequest> Parsedrequest;
    std::unordered_map<size_t, http_parser_settings> Parsersettings;

    virtual void onGET(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onPUT(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onPOST(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onCOPY(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onDELETE(const size_t Socket, HTTPRequest &Request) = 0;
    virtual void onStreamdecrypted(const size_t Socket, std::vector<uint8_t> &Stream);
};
#endif
