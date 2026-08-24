#include "SteamworksBackend.hpp"
#include <Networking/NetManager.hpp>

void SteamworksBackend::sendMessageToLobby(flatbuffers::Offset<CTSerialize::MessageHeader> out) {

}

void SteamworksBackend::recvMessages() {
    SteamNetworkingMessage_t* messageList[MAX_EDITOR_MESSAGES];
    auto numMessages = SteamNetworkingMessages()->ReceiveMessagesOnChannel(EDITOR_CHANNEL, messageList, MAX_EDITOR_MESSAGES);

    if (numMessages < 0) {
        log::warn("SteamworksBackend::receiveData(): Unknown error when receiving messages ({})", numMessages);
    }

    auto netManager = NetManager::get();
    // Its parsing time
    for (int i = 0; i < numMessages; i++) {
        SteamNetworkingMessage_t* msg = messageList[i];

        // This should create a msg->GetSize() sized data object,
        // and copy all the data from the msg over to it.
        uint8_t* data = new uint8_t[msg->GetSize()];
        memcpy(data, msg->GetData(), msg->GetSize());

        auto messageHeader = CTSerialize::GetMessageHeader(data);
        flatbuffers::Verifier verifier(data, msg->GetSize());
        bool isVerified = CTSerialize::VerifyMessageHeaderBuffer(verifier);

        if (!isVerified) {
            log::warn("Failed to verify message");
            msg->Release();
            delete[] data;
            continue;
        }

        if (LOG_RECV) {
            auto s = flatbuffers::FlatBufferToString(data, CTSerialize::MessageHeaderTypeTable());
            log::debug("RecvMessage:{}", s);
        }

        auto out = netManager->parseData(messageHeader, msg->m_identityPeer);

        if (!out) {
            log::warn("Something went wrong while parsing: {}", out.unwrapErr());
        }

        // Release and free up all the memory.
        // TODO: Call release earlier
        msg->Release();
        delete[] data; // Look see? exactly one call to delete per call to new. no memory leaks here!
    }
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
    log::info("Waiting for CreateLobby(lobbyType: {}, max: {}) to finish...", fmt::underlying(lobbyType), max);
    return;
}