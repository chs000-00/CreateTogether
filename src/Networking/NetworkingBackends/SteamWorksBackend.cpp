#include "SteamworksBackend.hpp"
#include <Networking/NetManager.hpp>

void SteamworksBackend::sendMessageToLobby() {

}

void SteamworksBackend::recvMessages() {
    SteamNetworkingMessage_t* messageList[MAX_EDITOR_MESSAGES_STEAMWORKS];

}

SteamworksBackend::~SteamworksBackend() {

}

void SteamworksBackend::startHosting(uint8_t max) {
    SteamMatchmaking()->CreateLobby(k_ELobbyTypeFriendsOnly, max);
    auto net = NetManager::get();
    if (net->m_isHosting) {
        log::error("NetManager is already hosting an instance");
        return;
    }
}