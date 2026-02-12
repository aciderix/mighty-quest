/*
    MQEL Online - Services multijoueur
*/
#pragma once
#include "SupabaseClient.hpp"
#include "../Auth/AuthManager.hpp"

namespace Online {
    class OnlineServices {
    public:
        // Matchmaking - Trouver des châteaux à attaquer
        static HttpResponse GetEligibleCastles(int minLevel, int maxLevel);
        
        // Combat - Démarrer et terminer une attaque
        static HttpResponse StartAttack(const std::string& castleId, const std::string& heroId);
        static HttpResponse EndAttack(const std::string& attackId, bool victory, int score);
        
        // Compte - Infos joueur
        static HttpResponse GetAccountInfo();
        
        // Classement
        static HttpResponse GetSeasonalRankings();
    };
}
