#include "NetManager.hpp"

void NetManager::update() {
    if (this->m_isSteamworksEnabled) {
        SteamAPI_RunCallbacks();
    }

    if (this->m_backend) {
        this->m_backend->recvMessages();
        // this->sendQueuedData();
        // this->m_cursorManager->update();
        // this->flushDictionaries();
    }
}
