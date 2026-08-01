#include "NetManager.hpp"

void NetManager::update() {
    if (this->m_isSteamworksLoaded) {
        SteamAPI_RunCallbacks();
    }

    if (this->m_backend) {
        this->m_backend->recvMessages();
        // this->sendQueuedData();
        // this->m_cursorManager->update();
        // this->flushDictionaries();
    }
}

bool NetManager::getIsInLobby() {
    return NetManager::get()->m_isInLobby;
}

bool NetManager::getWasDataSent() {
    return NetManager::get()->m_wasDataSent;
}