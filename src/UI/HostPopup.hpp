#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Button.hpp>
#include <Geode/utils/ColorProvider.hpp>
#include <Geode/utils/random.hpp>
#include <UIBuilder.hpp>

#include <Networking/NetManager.hpp>

using namespace geode::prelude;

class HostPopup : public geode::Popup {
protected:

    ELobbyType m_currentLobbyType;

    bool init() override;

    void startHosting();

public:
static HostPopup* create();
    void show() override;
};
