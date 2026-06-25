#pragma once

#include <Geode/Geode.hpp>

#include <steamworks/steamnetworkingtypes.h>
#include <steamworks/isteammatchmaking.h>

#include "HasCapableBackend.hpp"
#include <Constants.hpp>

using namespace geode::prelude;

class SteamworksBackend : HasCapableBackend {
    public:
        void sendMessageToLobby() override;
        void recvMessages() override;

        void connectToLobby();

        static void create(ELobbyType lobbyType, uint8_t max);
        
        ~SteamworksBackend();

        CSteamID m_hostID;

        // Steam LobbyID
        uint64 m_lobbyId;

        // A list of players in the lobby. sendMessage() sends the data to all of these users, and fetchMemberList() updates it.
        std::vector<SteamNetworkingIdentity> m_playersInLobby;

    private:
        // Steamnetworking has no way to kick/ban users. I think? Instead just remove the dudes access to m_playersInLobby and any
        // Further attempts to join (this member is specificaly for fetchMemberList())
        // None of this has timeouts cause I am too lazy to implement them so idk
        // std::vector<CSteamID> m_excludedMemberList;
};
