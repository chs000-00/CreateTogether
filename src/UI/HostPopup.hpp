#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Button.hpp>
#include <Geode/utils/ColorProvider.hpp>
#include <Geode/utils/random.hpp>
#include <Networking/NetManager.hpp>
#include <UIBuilder.hpp>

using namespace geode::prelude;

class HostPopup : public geode::Popup {
protected:

    ELobbyType m_currentLobbyType;

    // TODO-LIKELY-NEVER: Use a proper enum/something else instead of a bool flag
    bool m_useSteamworks = false;

    bool init() override;

    void startHosting();

public:
static HostPopup* create();
    void show() override;
};
