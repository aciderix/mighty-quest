# MQEL Online - Mighty Quest for Epic Loot Revival

🎮 **Resurrection du multijoueur en ligne pour The Mighty Quest For Epic Loot**

## 🚀 Fonctionnalités

- ✅ Authentification Legacy avec codes de récupération
- ✅ Matchmaking PvP en ligne
- ✅ Système d'attaque de châteaux
- ✅ Backend Supabase (base de données + Edge Functions)
- ✅ Protection anti-brute force

## 🔧 Compilation

### Prérequis
- Visual Studio 2019+ avec "Desktop development with C++"
- CMake 3.15+
- OpenSSL (pour SSL/HTTPS)

### Build
```bash
mkdir build && cd build
cmake -A x64 ..
cmake --build . --config Release
```

Le DLL sera généré dans `Bin/`

## 🎯 Utilisation

1. Copiez le DLL dans le dossier `Plugins/` du jeu
2. Lancez avec : `MightyQuest.exe -server_url https://Gameserver -environmentName mqel-live`

Ou utilisez `LaunchMQEL_Online.bat`

## 🔐 Codes de Récupération

À la création du compte, vous recevez un code : `MQEL-XXXX-YYYY-ZZZZ`

**⚠️ Notez-le !** C'est le seul moyen de récupérer votre compte sur un autre PC.

## 📡 Backend Supabase

Le serveur utilise Supabase comme backend :
- URL: `https://fsrfzdbmpywtsifmlria.supabase.co`
- 14 tables de base de données
- 6 Edge Functions pour l'API

## 📜 Licence

MIT License - Basé sur [MQELOffline_cpp](https://github.com/Hedgehogscience/MQELOffline_cpp)
