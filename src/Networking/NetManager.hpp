#pragma once

#include <Geode/Geode.hpp>
#include <Networking/NetworkingBackends/HasCapableBackend.hpp>
#include <Networking/NetworkingBackends/SteamworksBackend.hpp>
#include <Networking/NetworkingBackends/ENetBackend.hpp>
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

        // ... *gulp*
        SteamworksBackend* m_steamBackend;
        ENetBackend* m_eNetBackend;

        bool m_isHosting = false;
        bool m_isSteamworksLoaded = false;

        bool m_isInLobby = false;
        static bool getIsInLobby();

        // Was the data sent from another user?
        // Determines whether or not to run the original function. 
        // This is set to true temporarily inside a recv function.
        bool m_wasDataSent = false;
        
        // Returns this->m_wasDataSent
        static bool getWasDataSent();


        flatbuffers::FlatBufferBuilder m_builder;
};