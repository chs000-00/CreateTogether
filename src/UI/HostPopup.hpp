#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Button.hpp>
#include <Geode/utils/ColorProvider.hpp>
#include <UIBuilder.hpp>


using namespace geode::prelude;

class HostPopup : public geode::Popup {
protected:
    bool init();

    void startHosting();

public:
    static HostPopup* create();
};
