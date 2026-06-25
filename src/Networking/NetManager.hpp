#pragma once

#include <Geode/Geode.hpp>
#include <Networking/NetworkingBackends/HasCapableBackend.hpp>
#include <Types/Singleton.hpp>

#include <steamworks/isteamnetworkingmessages.h>
#include <steamworks/isteamuser.h>
#include <steamworks/isteammatchmaking.h>

#include <flatbuffers/flatbuffers.h>
#include <ctserialize_generated.h>

using namespace geode::prelude;


class NetManager : public Singleton<NetManager> {
    public:

        // Called each tick or smth idk how this shit works
        void update();

        HasCapableBackend* m_backend;
        bool m_isHosting = false;
        bool m_isSteamworksLoaded = false;

        flatbuffers::FlatBufferBuilder m_builder;
};