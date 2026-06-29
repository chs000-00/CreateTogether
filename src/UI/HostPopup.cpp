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

void HostPopup::alternateShow() {
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
        this->m_mainLayer->setRotation(-15);


        auto scaleAction = CCScaleTo::create(0.5, 1.0);
        
        auto rotateAction = CCRotateTo::create(0.5, 0.0);

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