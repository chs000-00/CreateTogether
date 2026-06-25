#include <Geode/Geode.hpp>
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

        auto fields = m_fields.self();
        fields->m_lobbyPopup = HostPopup::create();
        if (fields->m_lobbyPopup) {
            fields->m_lobbyPopup->show();
        }

        // if (!Mod::get()->setSavedValue("shown-beta-warning", true)) {
            FLAlertLayer::create(
                "Warning:",
                "Create together is currently in beta! Issues can and will arrise, so please make sure you backed up your levels beforehand!",
                "Continue"
            )->show();
        // }
    }

    // TODO: There might be an issue with exiting the lobby before you get to confirm exiting on the popup.

    void onSaveAndPlay(CCObject* sender) {
        // FLAlertLayer::create(
        //     "In Progress",
        //     "Playtesting is currently being worked at. It will be added in a future update.",
        //     "Ok"
        // )->show();
    }
};