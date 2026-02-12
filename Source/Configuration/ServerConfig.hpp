/*
    MQEL Online - Server Configuration
    Configuration pour le backend Supabase
*/

#pragma once
#include <string>

namespace Configuration
{
    namespace Supabase
    {
        constexpr const char* PROJECT_REF = "fsrfzdbmpywtsifmlria";
        constexpr const char* ANON_KEY = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImZzcmZ6ZGJtcHl3dHNpZm1scmlhIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NzA4MDIwNDgsImV4cCI6MjA4NjM3ODA0OH0.z6o8hP1FOPe1OsHLI9xwFvz8VIOg89JSugZI9Z1MlBE";
        
        inline std::string GetBaseURL() { return std::string("https://") + PROJECT_REF + ".supabase.co"; }
        inline std::string GetFunctionsURL() { return GetBaseURL() + "/functions/v1"; }
        inline std::string GetGameAuthURL() { return GetFunctionsURL() + "/game-auth"; }
        inline std::string GetAttackSelectionURL() { return GetFunctionsURL() + "/attack-selection"; }
        inline std::string GetAttackServiceURL() { return GetFunctionsURL() + "/attack-service"; }
        inline std::string GetServerCommandURL() { return GetFunctionsURL() + "/server-command"; }
        inline std::string GetAccountInfoURL() { return GetFunctionsURL() + "/account-info"; }
    }
    
    namespace Online
    {
        constexpr bool ONLINE_MODE = true;
        constexpr bool DEBUG_REQUESTS = true;
        constexpr int REQUEST_TIMEOUT = 30;
    }
}
