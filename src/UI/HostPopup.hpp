#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class HostPopup : public geode::Popup {
protected:
    bool init();

    void startHosting();

public:
    static HostPopup* create();
};
