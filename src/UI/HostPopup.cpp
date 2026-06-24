#include "HostPopup.hpp"


bool HostPopup::init() {
    if (!Popup::init(240.f, 160.f))
        return false;

    // convenience function provided by Popup
    // for adding/setting a title to the popup
    this->setTitle("Start Hosting");

    auto btn = geode::Button::createWithNode(
        ButtonSprite::create("Start Hosting"),
        [this](auto sender) {
            startHosting();
        }
    );
    m_mainLayer->addChildAtPosition(btn, Anchor::Bottom);

    return true;
}

void HostPopup::startHosting() {
    log::info("Started hosting");
}

HostPopup* HostPopup::create() {
    auto ret = new HostPopup();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}