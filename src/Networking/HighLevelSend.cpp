#include "HighLevelSend.hpp"

void addStringToIDList(IDList& uniqueIDList, const char* str) {
    auto netManager = NetManager::get();
    uniqueIDList.push_back(netManager->m_builder.CreateString(str));
}

void sendCreateObjects(const char* uniqueID, uint64_t objectID, CCPoint pos, float rotation, bool isHighDetail, bool noGlow, bool noEnter, bool flipX, bool flipY, float scaleX, float scaleY, short layer) {
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