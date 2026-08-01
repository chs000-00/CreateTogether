#include "SteamworksBackend.hpp"
#include <Networking/NetManager.hpp>

void SteamworksBackend::sendMessageToLobby(flatbuffers::Offset<CTSerialize::MessageHeader> out) {

}

void SteamworksBackend::recvMessages() {
    SteamNetworkingMessage_t* messageList[MAX_EDITOR_MESSAGES];
    auto numMessages = SteamNetworkingMessages()->ReceiveMessagesOnChannel(EDITOR_CHANNEL, messageList, MAX_EDITOR_MESSAGES);
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
    // net->m_steamBackend = new SteamworksBackend;
    // net->m_backend = net->m_steamBackend
    return;
}