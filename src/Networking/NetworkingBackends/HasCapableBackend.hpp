#pragma once

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
        virtual void sendMessageToLobby() = 0;
        virtual void recvMessages() = 0;

        bool m_isLobbyHost = false;
        bool m_isHosting = false;
};
