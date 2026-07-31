#include "SteamManager.hpp"

#ifdef STEAMWORKS

void SteamManager::onLobbyCreated(LobbyCreated_t* pCallback, bool bIOFailure) {

    if (pCallback->m_eResult == k_EResultOK) {
        log::info("Created Lobby with steamID {}.", pCallback->m_ulSteamIDLobby);

        // If you plan on using SteamMatchmaking please set these variables at some point when creating your lobby.
        SteamMatchmaking()->SetLobbyData(pCallback->m_ulSteamIDLobby, "lobby_mod_type", MOD_ID.c_str());
        SteamMatchmaking()->SetLobbyData(pCallback->m_ulSteamIDLobby, "lobby_mod_version", MOD_VERSION.c_str());

        // Other lobby data related stuff
        SteamMatchmaking()->SetLobbyData(pCallback->m_ulSteamIDLobby, "level_name", LevelEditorLayer::get()->m_level->m_levelName.c_str());
        SteamMatchmaking()->SetLobbyData(pCallback->m_ulSteamIDLobby, "host_name", SteamFriends()->GetPersonaName());

        geode::Notification::create(
        "You are now hosting a lobby",
            NotificationIcon::Success);

    } else {
        log::warn("Failed to create lobby with error code {}!", fmt::underlying(pCallback->m_eResult));
        geode::Notification::create(
            "Failed to create a lobby; " + convertLobbyResultToString(pCallback->m_eResult),
             NotificationIcon::Error);
    }
}

void SteamManager::onNetworkingMessagesSessionRequest(SteamNetworkingMessagesSessionRequest_t* pCallback) {
    SteamNetworkingMessages()->AcceptSessionWithUser(pCallback->m_identityRemote);
}

void SteamManager::onGameJoinRequest(GameLobbyJoinRequested_t* pCallback) {

    log::info("Game join was requested.");

    auto data = new GameLobbyJoinRequested_t;
    *data = *pCallback;

    geode::createQuickPopup(
        "Lobby",         
        fmt::format("Join {}'s Lobby?", SteamFriends()->GetFriendPersonaName(data->m_steamIDFriend)),
        "Cancel", "Join",
        [data](auto, bool btn2) {
            if (btn2) {
               log::debug("JoinLobbyRequest called with lobby: {} friendID: {} friendName: {}",
                    data->m_steamIDLobby.ConvertToUint64(),
                    data->m_steamIDFriend.ConvertToUint64(),
                    SteamFriends()->GetFriendPersonaName(data->m_steamIDFriend) // TODO: Remove this / privatize it better
                );
                
                // NetManager::get()->joinSteamLobby(callback);
            }
            delete data;
        }
        
    );
}


void SteamManager::onLobbyEnter(LobbyEnter_t* pCallback) {
    if (pCallback->m_EChatRoomEnterResponse != k_EChatRoomEnterResponseSuccess) {
        log::error("Failed to enter lobby with error code {}", pCallback->m_EChatRoomEnterResponse);
        FLAlertLayer::create(
            "Lobby Error",  
            fmt::format("Failed to enter lobby; <cr>Error {} </c>", pCallback->m_EChatRoomEnterResponse),
            "Ok"   
        )->show();
        return;
    }
}


void SteamManager::onLobbyChatUpdateWrapper(LobbyChatUpdate_t* pCallback) {

    auto netManager = NetManager::get();

    auto properBackend = dynamic_cast<SteamworksBackend*>(netManager->m_backend);

    if (pCallback->m_ulSteamIDUserChanged == properBackend->m_hostID.ConvertToUint64()) {
        if (pCallback->m_rgfChatMemberStateChange == k_EChatMemberStateChangeLeft || pCallback->m_rgfChatMemberStateChange == k_EChatMemberStateChangeDisconnected) {
            log::info("Host left server! Leaving lobby.");

            // properBackend->leaveLobby();

            switchToScene(CreatorLayer::create());

            FLAlertLayer::create(
                "Host stopped hosting",    
                "The host has stopped hosting the level!",  
                "Ok"
            )->show();

        }
    }

    log::debug("LobbyChatUpdateWrapper called. UserID: {} | UserName: {} | StateChange: {} | SteamIDMakingChange: {}", pCallback->m_ulSteamIDUserChanged, SteamFriends()->GetFriendPersonaName(pCallback->m_ulSteamIDUserChanged), pCallback->m_rgfChatMemberStateChange, pCallback->m_ulSteamIDMakingChange);


    // netManager->fetchMemberList();
}


#endif