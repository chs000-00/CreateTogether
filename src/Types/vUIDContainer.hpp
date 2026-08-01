#pragma once

#include <Geode/Geode.hpp>
#include "gdserialization_generated.h"

using namespace geode::prelude;

struct vUIDContainer {
    // uint64_t associatedID;
    uint32_t objectID;
    
    // Todo: test
    flatbuffers::Offset<CTSerialize::veryUniqueID> createOffset(flatbuffers::FlatBufferBuilder builder) {
        // return CTSerialize::CreateveryUniqueID(builder, this->associatedID, this->objectID);
        return CTSerialize::CreateveryUniqueID(builder, this->objectID);
    }
};