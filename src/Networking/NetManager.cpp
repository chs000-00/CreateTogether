#include "NetManager.hpp"
#include "Utills.hpp"
#include "ParseRecv.hpp"
#include <fmt/format.h>

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

void NetManager::hostEndedServerKick() {
    log::info("Host left server! Leaving lobby.");

    // properBackend->leaveLobby();

    switchToScene(CreatorLayer::create());

    FLAlertLayer::create(
        "Host stopped hosting",    
        "The host has <cy>stopped</c> hosting the level!",  
        "Ok"
    )->show();
}

MayFail NetManager::parseData(const CTSerialize::MessageHeader* msg, const bool isHost) {
    auto dmsg = msg->body();
    switch (msg->body_type()) {
        SERIALIZE_AND_RECV(CreateObjects)
        SERIALIZE_AND_RECV(DeleteObjects)
        SERIALIZE_AND_RECV(MoveObjects)
        SERIALIZE_AND_RECV(LevelSettingChange)
        SERIALIZE_AND_RECV(RotateObjects)
        SERIALIZE_AND_RECV(PasteObjects)
        SERIALIZE_AND_RECV(ModifyObjects)
        // SERIALIZE_AND_RECV(ChangeGroupID)
        // SERIALIZE_AND_RECV(ModifyObjectAdvancedOptions)
        // SERIALIZE_AND_RECV(ModifyObjectBasicOptions)
        // SERIALIZE_AND_RECV(ModifyObjectSpecialOptions)
        SERIALIZE_AND_RECV(ChangeDefaultColor)
        SERIALIZE_AND_RECV(RequestLevel, isHost)
        SERIALIZE_AND_RECV(ReturnLevelString, isHost)
        // SERIALIZE_AND_RECV(UpdateFont)
        SERIALIZE_AND_RECV(UpdateSong)
        SERIALIZE_AND_RECV(ChangeArt)
        SERIALIZE_AND_RECV(SpeedChange)
        SERIALIZE_AND_RECV(GameModeChange)
        // SERIALIZE_AND_RECV(AdminAction)
        SERIALIZE_AND_RECV(PlayerCursorData)
        SERIALIZE_AND_RECV(RequestForCursors)
        // SERIALIZE_AND_RECV(GlobedHandshake)

        case CTSerialize::MessageBody_NONE:
        default:
            return Err(fmt::format("Invalid Union Type: {}", fmt::underlying(msg->body_type())));
    }
    return Ok();
}