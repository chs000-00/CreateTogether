#pragma once

#include <Geode/Geode.hpp>
#include <Constants.hpp>
#include <enet.h>

using namespace geode::prelude;

class IntegratedDedicated {
public:
    void host(uint16_t port);
    void stopHost();

private:
    ENetAddress m_address = {0};
    ENetHost* m_server = nullptr;
    bool m_isHosting = false;
};

