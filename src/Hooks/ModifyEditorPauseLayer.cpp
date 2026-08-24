#include <Geode/Geode.hpp>
#include <Geode/binding/GameToolbox.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <UI/HostPopup.hpp>

using namespace geode::prelude;

class $modify(ModifiedEditorPauseLayer, EditorPauseLayer) {

    struct Fields {
        HostPopup* m_lobbyPopup = nullptr;
    };

    bool init(LevelEditorLayer* p0) {

        if (!EditorPauseLayer::init(p0)) {
            return false;
        }

        auto hostPopupButton = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSpriteFrameName("GJ_hammerIcon_001.png", (1.0F), geode::CircleBaseColor::Cyan, geode::CircleBaseSize::Small),	
            this,
            menu_selector(ModifiedEditorPauseLayer::onHostPopupButton)
        );

        auto menu = this->getChildByID("guidelines-menu");
        menu->addChild(hostPopupButton);
        hostPopupButton->setID("host-button"_spr);
        menu->updateLayout();

        if (!Mod::get()->getSavedValue<bool>("shown-beta-warning")) {
            auto sickassParticles = CCParticleSystemQuad::create();
            GameToolbox::particleFromString(
                "110a10a3a0.25a33a90a26a0a10a15a15a0a0a0a0a99a0a40a1a0a0a0.211765a0a0.733333a0a1a0a1a0a0a1a0a0a0.341176a0.17a0.972549a0.73a0.858824a0.69a1a0.63a0a0a0a0a0a0a0a0a0a0a0a2a1a0a0a0a159a0a0a0a0a0a0a0a0a0a0a0a0a0a0",
                sickassParticles,
                false
            );
            sickassParticles->setZOrder(-5);
            hostPopupButton->addChildAtPosition(sickassParticles, Anchor::Center);
        }
        return true;
    }

    void onHostPopupButton(CCObject* sender) {
        // auto netManager = NetManager::get();

        // if (!NetManager::getIsInLobby()) {
        //     // TODO: Shorten this
        //     m_fields->m_lobbyPopup = LobbyPopup::create(eLobbyHostPopup);
            
        // } 
        // else if (netManager->m_isHost) {
        //     m_fields->m_lobbyPopup = LobbyPopup::create(eLobbyHostingPopup);
        // } 
        // else {
        //     m_fields->m_lobbyPopup = LobbyPopup::create(eLobbyJoinedUserPopup);
        // }


        // // Make sure we really did in fact create a popup
        // if (m_fields->m_lobbyPopup) {
        //     m_fields->m_lobbyPopup->show();
        // }
        
        log::debug("onHostPopupButton() called");
        auto fields = m_fields.self();
        fields->m_lobbyPopup = HostPopup::create();
        if (fields->m_lobbyPopup) {
            fields->m_lobbyPopup->show();
        }

        if (!Mod::get()->setSavedValue("shown-beta-warning", true)) {
            FLAlertLayer::create(
                "Warning:",
                "Create together is currently in beta! <co>Issues can and will arrise</c>, so please make sure you <cp>back up your levels</c> beforehand!",
                "Continue"
            )->show();
        }
    }

    // TODO: There might be an issue with exiting the lobby before you get to confirm exiting on the popup.
    void onSaveAndPlay(CCObject* sender) {
        log::debug("onSaveAndPlay() called");
        if (NetManager::get()->m_isHosting) {
            FLAlertLayer::create(
                "In Progress",
                "Playtesting is currently being worked at. It will be added in a future update.",
                "Ok"
            )->show();
        } else {
            ModifiedEditorPauseLayer::onSaveAndPlay(sender);
        }
    }
};