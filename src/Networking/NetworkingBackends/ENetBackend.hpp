#pragma once

#include <Geode/Geode.hpp>
#include "HasCapableBackend.hpp"
#include <Constants.hpp>
#include <enet.h>

using namespace geode::prelude;

class ENetBackend : HasCapableBackend {
    public:
        void sendMessageToLobby() override;
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

