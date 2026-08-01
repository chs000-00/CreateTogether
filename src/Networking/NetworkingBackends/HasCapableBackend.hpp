#pragma once

#include <Geode/Geode.hpp>
#include <flatbuffers/flatbuffers.h>
#include <ctserialize_generated.h>

using namespace geode::prelude;

// Fully virtual class containing the following:

// sendMessageToLobby(); - Sends a flatbuf. message to everyone else in the lobby
// recvMessages(); - Recvs. a list of queued messages to parse

// Possibly?
// sendCursorMessage()
// recvCursorMessage()

// (?) startHostingServer(); - Is able to start hosting server

// TODO: Implement a way to identify users
// std::vector<UserIdentity> m_excludedMemberList;


class HasCapableBackend {
    public:
        // Sends an entire message to everyone in the lobby
        virtual void sendMessageToLobby(flatbuffers::Offset<CTSerialize::MessageHeader> out) = 0;

        virtual void recvMessages() = 0;

        // When leaving the lobby the dtor gets called.
        virtual ~HasCapableBackend() {
            log::info("Deconstructing HasCapableBackend");
        }

        bool m_isLobbyHost = false;
};
