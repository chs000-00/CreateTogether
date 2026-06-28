#include "HostPopup.hpp"

bool HostPopup::init() {
    if (!Popup::init(340.f, 250.f, "GE_square02.png"))
        return false;

    // convenience function provided by Popup
    // for adding/setting a title to the popup
    this->setTitle("Start Hosting");

    Build<CCNode>::create()
        .layout(
            Build<ColumnLayout>::createWithAligns(AxisAlignment::Center, AxisAlignment::Center)
            .autoScale(false)
        ).contentSize({300, 200})
        .children(

            Build<CCMenu>::create()
                .layout(
                    Build<RowLayout>::createWithAligns(AxisAlignment::Center, AxisAlignment::Center)
                    .autoScale(false)
                ).contentSize({300, 200})
                .children(
                    Build<CCMenuItemToggler>::createToggle([](CCMenuItemToggler* toggler) {
                        log::info("toggled invite! {}", toggler->isOn()); 
                    }).scale(0.75),
                    Build<CCLabelBMFont>::create("Require Invite", "bigFont.fnt").scale(0.75)
                ).updateLayout(),

            Build<CCMenu>::create()
                .layout(
                    Build<RowLayout>::createWithAligns(AxisAlignment::Center, AxisAlignment::Center)
                    .autoScale(false)
                ).contentSize({300, 200})
                .children(
                    Build<CCMenuItemToggler>::createToggle([](CCMenuItemToggler* toggler) {
                        log::info("toggled steamworks! {}", toggler->isOn()); 
                    }).scale(0.75),
                    Build<CCLabelBMFont>::create("Use Steamworks", "bigFont.fnt").scale(0.75)
                ).updateLayout()

        ).updateLayout()
        .anchorPoint({0.5, 0.5})
        .parentAtPos(m_mainLayer, Anchor::Center);

    auto btn = geode::Button::createWithNode(
        ButtonSprite::create("Start Hosting", 0, false, "goldFont.fnt", "GJ_button_05.png", .0f, 1.4f),
        [this](auto sender) {
            startHosting();
        }
    );

    m_mainLayer->addChildAtPosition(btn, Anchor::Bottom, {0, 25});
    this->m_noElasticity = true;

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