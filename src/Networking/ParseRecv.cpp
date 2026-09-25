#include "ParseRecv.hpp"
#include "Hooks/ModifyGameObject.hpp"

MayFail PRecv::recvCreateObjects(const CTSerialize::CreateObjects* msg) {
    auto minObj = msg->obj();
    cocos2d::CCPoint gameObjectPos = {static_cast<float>(minObj->pos()->x()), static_cast<float>(minObj->pos()->y())};

    // TODO: nullptr check this
    // TODO: Figure this out
    auto level = static_cast<MyLevelEditorLayer*>(LevelEditorLayer::get());
    // TODO: Figure if a race condition is possible
    
    NetManager::get()->m_wasDataSent = true;
    GameObject* placedGameObject = level->createObject(minObj->objID(), gameObjectPos, false);
    NetManager::get()->m_wasDataSent = false;

    placedGameObject->setRotation(minObj->rotation());
    placedGameObject->m_isHighDetail = minObj->isHighDetail();
    placedGameObject->m_hasNoGlow = minObj->noGlow();
    placedGameObject->m_isDontEnter = minObj->noEnter();

    if(auto flip = minObj->flip()) {
        placedGameObject->setFlipX(flip->flipX());
        placedGameObject->setFlipY(flip->flipY());
    }

    if (auto scale = minObj->scale()) {
        placedGameObject->setScaleX(scale->x());
        placedGameObject->setScaleY(scale->y());
    }

    IDGameObject* betterPlacedGameObject = static_cast<IDGameObject*>(placedGameObject);
    
    auto vuid = vUIDContainer(/* minObj->uniqueID()->associatedID(), */ minObj->uniqueID()->objectID());

    betterPlacedGameObject->m_fields->m_veryUniqueID = vuid;
    level->m_fields->m_pUniqueIDOfGameObject->setObject(placedGameObject, vuid);
    return Ok();
}

MayFail PRecv::recvDeleteObjects(const CTSerialize::DeleteObjects* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvMoveObjects(const CTSerialize::MoveObjects* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvLevelSettingChange(const CTSerialize::LevelSettingChange* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvRotateObjects(const CTSerialize::RotateObjects* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvPasteObjects(const CTSerialize::PasteObjects* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvModifyObjects(const CTSerialize::ModifyObjects* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvChangeDefaultColor(const CTSerialize::ChangeDefaultColor* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvRequestLevel(const CTSerialize::RequestLevel* msg, bool trusted) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvReturnLevelString(const CTSerialize::ReturnLevelString* msg, bool trusted) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvUpdateSong(const CTSerialize::UpdateSong* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvChangeArt(const CTSerialize::ChangeArt* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvSpeedChange(const CTSerialize::SpeedChange* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvGameModeChange(const CTSerialize::GameModeChange* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvPlayerCursorData(const CTSerialize::PlayerCursorData* msg) {
 return Err("Correct union was unimplemented");
}

MayFail PRecv::recvRequestForCursors(const CTSerialize::RequestForCursors* msg) {
 return Err("Correct union was unimplemented");
}