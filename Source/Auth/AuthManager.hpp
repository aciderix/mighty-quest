/*
    AuthManager.hpp - Système d'authentification pour MQEL Online
    Mode Legacy avec codes de récupération (sans Steam)
    
    Sécurité:
    - Code de récupération: MQEL-XXXX-YYYY-ZZZZ (32^12 combinaisons)
    - Hashé en SHA-256 côté serveur
    - Rate limiting: 5 tentatives/heure max
    - Permet de récupérer son compte sur un autre PC
*/

#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <functional>
#include <filesystem>
#include "Configuration/ServerConfig.hpp"

#ifdef _WIN32
    #include <windows.h>
    #include <shlobj.h>
#endif

namespace MQEL {
namespace Auth {

    struct AuthData {
        std::string legacyId;
        std::string displayName;
        std::string playerId;
        std::string recoveryCode;
        bool isAuthenticated = false;
        bool isNewAccount = false;
    };

    struct AuthResult {
        bool success = false;
        std::string message;
        std::string errorCode;
        AuthData data;
        int attemptsRemaining = -1;
    };

    class AuthManager {
    private:
        AuthData m_currentAuth;
        std::string m_credentialsPath;
        
        std::string generateMachineId() {
            std::string machineInfo;
            #ifdef _WIN32
                char computerName[MAX_COMPUTERNAME_LENGTH + 1];
                DWORD size = sizeof(computerName);
                if (GetComputerNameA(computerName, &size)) machineInfo += computerName;
                char userName[256];
                DWORD userSize = sizeof(userName);
                if (GetUserNameA(userName, &userSize)) { machineInfo += "_"; machineInfo += userName; }
            #else
                machineInfo = "linux_user";
            #endif
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(100000, 999999);
            machineInfo += "_" + std::to_string(dis(gen));
            std::hash<std::string> hasher;
            std::stringstream ss;
            ss << "MQEL_LEGACY_" << std::hex << hasher(machineInfo);
            return ss.str();
        }
        
        std::string getCredentialsPath() {
            if (!m_credentialsPath.empty()) return m_credentialsPath;
            #ifdef _WIN32
                char appData[MAX_PATH];
                if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, appData))) {
                    m_credentialsPath = std::string(appData) + "\\MQEL\\";
                    std::filesystem::create_directories(m_credentialsPath);
                    m_credentialsPath += "credentials.dat";
                }
            #else
                m_credentialsPath = std::string(getenv("HOME")) + "/.mqel/credentials.dat";
            #endif
            return m_credentialsPath;
        }
        
        bool saveCredentials(const std::string& legacyId, const std::string& displayName) {
            std::ofstream file(getCredentialsPath());
            if (!file.is_open()) return false;
            file << legacyId << "\n" << displayName;
            return true;
        }
        
        bool loadCredentials(std::string& legacyId, std::string& displayName) {
            std::ifstream file(getCredentialsPath());
            if (!file.is_open()) return false;
            std::getline(file, legacyId);
            std::getline(file, displayName);
            return !legacyId.empty();
        }

    public:
        AuthManager() {}
        bool hasLocalCredentials() { std::string id, name; return loadCredentials(id, name); }
        
        template<typename Callback>
        void registerAccount(const std::string& displayName, Callback callback);
        
        template<typename Callback>
        void login(Callback callback);
        
        template<typename Callback>
        void recoverAccount(const std::string& recoveryCode, Callback callback);
        
        template<typename Callback>
        void regenerateRecoveryCode(Callback callback);
        
        void logout() {
            std::filesystem::remove(getCredentialsPath());
            m_currentAuth = AuthData();
        }
        
        const AuthData& getCurrentAuth() const { return m_currentAuth; }
        bool isAuthenticated() const { return m_currentAuth.isAuthenticated; }
        std::string getPlayerId() const { return m_currentAuth.playerId; }
        std::string getDisplayName() const { return m_currentAuth.displayName; }
    };

} // namespace Auth
} // namespace MQEL
