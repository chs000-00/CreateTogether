#pragma once

#include <Geode/Geode.hpp>

#include <steamworks/steamnetworkingtypes.h>
#include <steamworks/isteammatchmaking.h>

#include "HasCapableBackend.hpp"

using namespace geode::prelude;

class SteamworksBackend : HasCapableBackend {
    public:
        void sendMessageToLobby() override;
        void recvMessages() override;

        void connectToLobby();

        void startHosting(uint8_t max);

        CSteamID m_hostID;
        
};
