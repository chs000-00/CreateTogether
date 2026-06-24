#pragma once

#include <Geode/Geode.hpp>
#include <Networking/NetworkingBackends/HasCapableBackend.hpp>
#include <Types/Singleton.hpp>

#include <flatbuffers/flatbuffers.h>
#include <ctserialize_generated.h>

using namespace geode::prelude;


class NetManager : public Singleton<NetManager> {
    public:
        HasCapableBackend* backend;
        bool m_isHosting = false;

        flatbuffers::FlatBufferBuilder m_builder;
};