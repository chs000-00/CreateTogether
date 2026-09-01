#include "HostPopup.hpp"

// TODO: Add an enum to show different popups based on if you joined/hosted/didn't
bool HostPopup::init() {
    if (!Popup::init(340.f, 250.f, "geode.loader/GE_square02.png"))
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
                    Build<CCMenuItemToggler>::createToggle([this](CCMenuItemToggler* toggler) {
                        log::info("toggled invite! {}", toggler->isOn()); 
                        if (!toggler->isOn()) {
                            this->m_currentLobbyType = k_ELobbyTypeFriendsOnly;
                        } else {
                            this->m_currentLobbyType = k_ELobbyTypePrivate;
                        }
                    }).scale(0.75),
                    Build<CCLabelBMFont>::create("Require Invite", "bigFont.fnt").scale(0.75),
                    Build<CCSprite>::createSpriteName(
                        "GJ_infoIcon_001.png"
                    ).scale(0.6)
                    .intoMenuItem([this] {
                        FLAlertLayer::create(
                            "Info:",
                            "<cr>Note:</c> This setting <cy>only</c> applies for levels hosted with <cf>Steamworks</c>\nShould your friends be able to join you <cp>without a prior invite?</c>",
                            "ok"
                        )->show();
                    })
                ).updateLayout(),

            Build<CCMenu>::create()
                .layout(
                    Build<RowLayout>::createWithAligns(AxisAlignment::Center, AxisAlignment::Center)
                    .autoScale(false)
                ).contentSize({300, 200})
                .children(
                    Build<CCMenuItemToggler>::createToggle([](CCMenuItemToggler* toggler) {
                        log::info("Toggled steamworks! {}", toggler->isOn()); 
                    }).scale(0.75),
                    Build<CCLabelBMFont>::create("Use Steamworks", "bigFont.fnt").scale(0.75),
                        Build<CCSprite>::createSpriteName(
                            "GJ_infoIcon_001.png"
                        ).scale(0.6)
                        .intoMenuItem([this] {
                            FLAlertLayer::create(
                                "Info:",
                                "<cd>Host using steam's built-in</c> <cf>p2p servers</c>.\nEnabling this setting means <cg>you are not required to port-forward</c>, and <cy>you can join via steam-invites</c>, <cr>however</c> only PC players with steam may join.",
                                "ok"
                            )->show();
                        })
                ).updateLayout()

        ).updateLayout()
        .anchorPoint({0.5, 0.5})
        .parentAtPos(m_mainLayer, Anchor::Center);

    Build<ButtonSprite>::create(
        "Start Hosting",
        "goldFont.fnt",
        "GJ_button_05.png",
        1.4f
    ).intoMenuItem([this] {
            startHosting();
        }) // returns Build<CCMenuItemSpriteExtra>
    .intoNewParent(CCMenu::create()) // returns Build<CCMenu>
    .parentAtPos(m_mainLayer, Anchor::Bottom, {0, 25});

    return true;
}

void HostPopup::startHosting() {
    log::info("Started hosting");
    auto net = NetManager::get();
    SteamworksBackend::create(m_currentLobbyType, MAX_USERS);
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

// Makes the popup ~-=look awesome=-~
void HostPopup::show() {
    if (this->m_noElasticity) {
        auto scene = CCDirector::sharedDirector()->m_pRunningScene;
        if (this->m_scene) {
            scene = static_cast<CCScene*>(this->m_scene);
        } else {
            int highestZChild;
            if (scene->CCScene::getHighestChildZ() + 1 >= 105) {
                highestZChild = scene->CCScene::getHighestChildZ() + 1;
            } else {
                highestZChild = 105;
            }
            this->m_ZOrder = highestZChild;
        }
        if (!this->m_ZOrder) {
            this->m_ZOrder = 105;
        }
        scene->addChild(this);

    } else {
        
        float opacity = this->getOpacity();
        this->m_mainLayer->setScale(0);


        CCActionInterval * rotateAction;

        // Haha funny easter egg
        if (!geode::utils::random::chance(0.02f)) {
            this->m_mainLayer->setRotation(-15);
            rotateAction = CCRotateTo::create(0.5, 0.0);
        } else {
            this->m_mainLayer->setRotation(0);
            rotateAction = CCRotateBy::create(0.5, 360.0);
        }

        auto scaleAction = CCScaleTo::create(0.5, 1.0);
        
        auto easedScaleAction = CCEaseBackOut::create(scaleAction);
        auto easedRotationAction = CCEaseBackOut::create(rotateAction);

        this->m_mainLayer->runAction(easedScaleAction);
        this->m_mainLayer->runAction(easedRotationAction);

        auto scene = CCDirector::sharedDirector()->m_pRunningScene;

        if (this->m_scene) {
            scene = static_cast<CCScene *>(this->m_scene);
        } else {
            int highestZChild;     

            if (scene->getHighestChildZ() + 1 >= 105) {
                highestZChild = scene->getHighestChildZ() + 1;
            } else {
                highestZChild = 105;
            }
            this->m_ZOrder = highestZChild;

        }

        if (!this->m_ZOrder) {
            this->m_ZOrder = 105;
        }

        scene->addChild(this);
        this->setOpacity(0); // Hide the FLAlertLayer
        auto fadeAction = CCFadeTo::create(0.14, opacity); // Fade in the FLAlertLayer
        this->runAction(fadeAction);

    }
    
    this->setVisible(true);
}