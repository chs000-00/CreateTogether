#pragma once

#include <Geode/Geode.hpp>
#include <Networking/NetManager.hpp>
#include <Networking/NetworkingBackends/SteamworksBackend.hpp>
#include <Types/Singleton.hpp>
#include <Constants.hpp>
#include <Utills.hpp>
#include <steamworks/isteamnetworkingmessages.h>
#include <steamworks/isteamuser.h>
#include <steamworks/isteammatchmaking.h>



using namespace geode::prelude;



class SteamManager: public Singleton<SteamManager> {
    public:
        bool m_isSteamworksLoaded = false;

        SteamAPICall_t m_lobbyCreated;
        // SteamAPICall_t m_lobbyJoined;

        CCallResult< SteamManager, LobbyCreated_t > m_isInLobbyCallResult;
        CCallResult< SteamManager, LobbyEnter_t > m_enterLobbyCallResult;

        void onLobbyCreated(LobbyCreated_t* pCallback, bool bIOFailure);
        void onLobbyEnter(LobbyEnter_t* pCallback, bool bIOFailure);

    private:

        #ifdef STEAMWORKS

        STEAM_CALLBACK(SteamManager, onGameJoinRequest, GameLobbyJoinRequested_t);
        STEAM_CALLBACK(SteamManager, onLobbyChatUpdateWrapper, LobbyChatUpdate_t);
        STEAM_CALLBACK(SteamManager, onLobbyEnter, LobbyEnter_t);
        STEAM_CALLBACK(SteamManager, onNetworkingMessagesSessionRequest, SteamNetworkingMessagesSessionRequest_t);
        
        #endif
};