#include "SteamworksBackend.hpp"
#include <Networking/NetManager.hpp>

void SteamworksBackend::sendMessageToLobby() {

}

void SteamworksBackend::recvMessages() {
    SteamNetworkingMessage_t* messageList[MAX_EDITOR_MESSAGES_STEAMWORKS];

}

SteamworksBackend::~SteamworksBackend() {

}

void SteamworksBackend::create(ELobbyType lobbyType, uint8_t max) {

    auto net = NetManager::get();
    if (net->m_isHosting) {
        log::error("NetManager is already hosting an instance");
        return;
    }

    SteamMatchmaking()->CreateLobby(lobbyType, max);

    return;
}