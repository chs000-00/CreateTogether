#include "HighLevelSend.hpp"

void addStringToIDList(IDList& uniqueIDList, vUIDContainer objectID) {
    auto netManager = NetManager::get();
    uniqueIDList.push_back(objectID.createOffset(netManager->m_builder));
}

void sendCreateObjects(vUIDContainer uniqueID, uint64_t objectID, CCPoint pos, float rotation, bool isHighDetail, bool noGlow, bool noEnter, bool flipX, bool flipY, float scaleX, float scaleY, short layer) {
    auto netManager = NetManager::get();
    auto objectPos = CTSerialize::CCPosI(pos.x, pos.y);
    auto flip = CTSerialize::ObjectFlip(flipX, flipY);
    auto objectScale = CTSerialize::NodeScale(scaleX, scaleY);
    auto uniqueIDOffset = CTSerialize::CreateveryUniqueID(netManager->m_builder);
    auto minObj = CTSerialize::CreateGDGameObjectMin(netManager->m_builder, uniqueIDOffset, objectID, &objectPos, rotation, isHighDetail, noGlow, noEnter, &flip, &objectScale, layer); //uhh add stuff here
    auto createObjectsOffset = CTSerialize::CreateCreateObjects(netManager->m_builder, minObj);
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_CreateObjects, createObjectsOffset.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}


void sendDeleteObjects(IDList& uniqueIDList) {
    auto netManager = NetManager::get();
    auto deleteObjectsMessage = CTSerialize::CreateDeleteObjects(netManager->m_builder, netManager->m_builder.CreateVector(uniqueIDList));
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_DeleteObjects, deleteObjectsMessage.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendMoveObjects(vUIDContainer uniqueID, CCPoint offset) {
    // auto netManager = NetManager::get();
    // auto offsetPos = CTSerialize::CCPos(offset.x, offset.y);
    // auto moveObjectsOffset = CTSerialize::CreateMoveObjectsDirect(netManager->m_builder, uniqueID, &offsetPos);
    // auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_MoveObjects, moveObjectsOffset.Union());
    // netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    // netManager->m_builder.Clear();
}

void sendLevelSettingChange(uint16 settingID) {
    auto netManager = NetManager::get();
    auto levelSettingChangeOffset = CTSerialize::CreateLevelSettingChange(netManager->m_builder, settingID);
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_LevelSettingChange, levelSettingChangeOffset.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

// TODO: Remove hardcoded value / use enums
void sendSpawnGroupChange(int spawngroup) {
    auto netManager = NetManager::get();
    auto levelSettingChangeOffset = CTSerialize::CreateLevelSettingChange(netManager->m_builder, 13, spawngroup);
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_LevelSettingChange, levelSettingChangeOffset.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendRotateObjects(IDList& uniqueIDList, float rotation, CCPoint anchor) {
    auto netManager = NetManager::get();
    auto objectPos = CTSerialize::CCPos(anchor.x, anchor.y);
    auto rotateObjectsOffset = CTSerialize::CreateRotateObjects(netManager->m_builder, rotation, &objectPos, netManager->m_builder.CreateVector(uniqueIDList));
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_RotateObjects, rotateObjectsOffset.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendPasteObjects(IDList& uniqueIDList, const char* copyStr) {
    auto netManager = NetManager::get();
    auto pasteObjectsMessage = CTSerialize::CreatePasteObjects(netManager->m_builder, netManager->m_builder.CreateVector(uniqueIDList), netManager->m_builder.CreateString(copyStr));
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_PasteObjects, pasteObjectsMessage.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendModifyObjects(IDList& uniqueIDList, const char* copyStr) {
    auto netManager = NetManager::get();
    auto modifyObjectsMessage = CTSerialize::CreateModifyObjects(netManager->m_builder, netManager->m_builder.CreateVector(uniqueIDList), netManager->m_builder.CreateString(copyStr));
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_ModifyObjects, modifyObjectsMessage.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendChangeDefaultColor(int groupID, ccColor3B currentColor, ccHSVValue hsv, bool blending, float opacity, bool copyOpacity, int copyColorID) {
    auto netManager = NetManager::get();
    auto currentColorOffset = CTSerialize::CCColor3B(currentColor.r, currentColor.g, currentColor.b);
    auto hsvOffset = CTSerialize::CCHsvValue(hsv.h, hsv.s, hsv.v, hsv.absoluteSaturation, hsv.absoluteBrightness);
    auto changeDefaultColor = CTSerialize::CreateChangeDefaultColor(netManager->m_builder, groupID, &currentColorOffset, &hsvOffset, blending, opacity);
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_ChangeDefaultColor, changeDefaultColor.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendRequestLevel() {
    auto netManager = NetManager::get();
    auto requestLevelOffset = CTSerialize::CreateRequestLevel(netManager->m_builder);
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_RequestLevel, requestLevelOffset.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendReturnLevelString() {
    // auto netManager = NetManager::get();
    // auto level = static_cast<MyLevelEditorLayer*>(LevelEditorLayer::get());

    // if (!level) {
    //     log::warn("sendReturnLevelString: LevelEditorLayer::get() returned nullptr");
    //     return;
    // }

    // IDList idlist;

    // for (auto obj : CCArrayExt<IDGameObject*>(level->m_objects)) {
    //     addStringToIDList(idlist, obj->m_fields->m_veryUniqueID.c_str());
    // }

    // // auto dict = new DS_Dictionary();
    // // level->m_level->encodeWithCoder(dict);
    // // auto data = dict->saveRootSubDictToString();
    // // delete dict;

    // auto data = level->getLevelString();

    // auto returnLevelStringOffset = CTSerialize::CreateReturnLevelString(netManager->m_builder, netManager->m_builder.CreateVector(idlist), netManager->m_builder.CreateString(data));
    // auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_ReturnLevelString, returnLevelStringOffset.Union());
    // netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    // netManager->m_builder.Clear();
}

void sendUpdateSong(uint64_t songID) {
    auto netManager = NetManager::get();
    auto updateSongMessage = CTSerialize::CreateUpdateSong(netManager->m_builder, songID);
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_UpdateSong, updateSongMessage.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendChangeArt(SelectArtType artType, int artID, int line) {
    auto netManager = NetManager::get();
    auto changeArtMessage = CTSerialize::CreateChangeArt(netManager->m_builder, static_cast<CTSerialize::ArtType>(artType), artID, line);
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_ChangeArt, changeArtMessage.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendSpeedChange(int speed) {
    auto netManager = NetManager::get();
    auto speedChangeMessage = CTSerialize::CreateSpeedChange(netManager->m_builder,  static_cast<CTSerialize::Speed>(speed));
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_SpeedChange, speedChangeMessage.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}

void sendGameModeChange(uint8 gameMode) {
    auto netManager = NetManager::get();
    auto gameModeMessage = CTSerialize::CreateGameModeChange(netManager->m_builder, gameMode);
    auto messageHeaderOffset = CTSerialize::CreateMessageHeader(netManager->m_builder, CTSerialize::MessageBody_GameModeChange, gameModeMessage.Union());
    netManager->m_backend->sendMessageToLobby(messageHeaderOffset);
    netManager->m_builder.Clear();
}
