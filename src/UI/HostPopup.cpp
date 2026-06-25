#include "HostPopup.hpp"

bool HostPopup::init() {
    if (!Popup::init(300.f, 200.f))
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

    Build<CCLabelBMFont>::create("Friends Only", "bigFont.fnt").scale(0.5);
    Build<CCLabelBMFont>::create("Invite Only", "bigFont.fnt").scale(0.5);
    Build<CCLabelBMFont>::create("Public", "bigFont.fnt").scale(0.5);

    // auto checkMarkMenu = CCMenu::create();
    // checkMarkMenu->setLayout(RowLayout::create());
    // checkMarkMenu->setContentSize(this->getContentSize());

    // auto publicText = CCLabelBMFont::create("Public Lobby", "bigFont.fnt");
    // auto publicToggle = CCMenuItemExt::createTogglerWithStandardSprites(
    //     1.0f,
    //     [this](CCMenuItemToggler* sender) {
    //         log::debug("Setting isPublic to {}.", !sender->isOn());
    //     }
    // );

    // // TODO: Fix this reseting or something idfk
    // // publicToggle->toggle();

    // checkMarkMenu->addChild(publicText);
    // checkMarkMenu->addChild(publicToggle);
    // checkMarkMenu->updateLayout();
    // checkMarkMenu->setScale(0.5f);
    // this->m_buttonMenu->addChildAtPosition(checkMarkMenu, Anchor::Center);

    // m_mainLayer->addChildAtPosition(lobbyTypeDropdown, Anchor::Center);
    m_mainLayer->addChildAtPosition(btn, Anchor::Bottom, {0, 20});

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