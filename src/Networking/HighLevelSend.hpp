#pragma once

#include <Geode/Geode.hpp>
#include <Networking/NetManager.hpp>
#include <Utills.hpp>
#include <flatbuffers/flatbuffers.h>
#include <ctserialize_generated.h>


// Too lazy to write out std::vector<flatbuffers::Offset<flatbuffers::String>>
typedef std::vector<flatbuffers::Offset<flatbuffers::String>> IDList;

void addStringToIDList(IDList& uniqueIDList, const char* str);

void sendCreateObjects(const char* uniqueID, uint64_t objectID, CCPoint pos, float rotation, bool isHighDetail, bool noGlow, bool noEnter, bool flipX, bool flipY, float scaleX, float scaleY, short layer);
