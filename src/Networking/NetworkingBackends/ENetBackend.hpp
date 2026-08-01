#pragma once

#include <Geode/Geode.hpp>
#include <Constants.hpp>
#include "HasCapableBackend.hpp"
#include <enet.h>
#include <flatbuffers/flatbuffers.h>
#include <ctserialize_generated.h>

using namespace geode::prelude;

class ENetBackend : HasCapableBackend {
    public:
        void sendMessageToLobby(flatbuffers::Offset<CTSerialize::MessageHeader> out) override;
        void recvMessages() override;

        void connectToLobby();

        using CreateENetBackendTask = Task<Result<ENetBackend*>>;
        static CreateENetBackendTask create(std::string host, uint16_t port);
        
        ~ENetBackend();

        ENetHost* m_client;
        ENetAddress m_address;
        ENetEvent m_event;
        ENetPeer* m_peer;

        bool m_fullyInitialized;
};

