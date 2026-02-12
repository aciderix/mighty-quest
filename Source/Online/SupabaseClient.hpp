/*
    MQEL Online - Supabase HTTP Client
*/
#pragma once
#include <string>
#include <functional>
#include "../Configuration/ServerConfig.hpp"

#ifdef _WIN32
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
#endif

namespace Online {
    inline std::string g_AuthToken = "";
    inline std::string g_PlayerId = "";
    
    struct HttpResponse {
        int statusCode = 0;
        std::string body;
        bool success = false;
        std::string error;
    };
    
    class SupabaseClient {
    public:
        static HttpResponse Get(const std::string& url);
        static HttpResponse Post(const std::string& url, const std::string& body);
        static HttpResponse Put(const std::string& url, const std::string& body);
        static HttpResponse Delete(const std::string& url);
    };
}
