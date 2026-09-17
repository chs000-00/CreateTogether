#pragma once

#include <Geode/Geode.hpp>
#include <Geode/binding/GhostTrailEffect.hpp>
#include <Geode/binding/HardStreak.hpp>
#include <Geode/binding/SimplePlayer.hpp>

using namespace geode::prelude;

// Thanks wavecursor!
class CursorUnit : public cocos2d::CCNode, public cocos2d::CCRGBAProtocol  {
public:

    struct CursorData {
        int cursorColor1;
        int cursorColor2;
        int cursorID;
        int cursorGlowColor;
        int playerTrail;
        bool cursorHasGlow;
    };

    static CursorUnit* create(const CursorData& cursorData);
    // static CursorUnit* create(int cursorColor1, int cursorColor2);

    inline static CursorData defaultCursorData(int cursorColor1, int cursorColor2) {
        return CursorData(
            cursorColor1,
            cursorColor2,
            1,
            true,
            0
        );
    }

    // TODO: Finish
    inline static bool validateCursorData(const CursorData& cursorData) {
        return true;
    }

    void updateCursor(const CursorData& cursorData);
    SimplePlayer* getSimplePlayer();

    void update(float dt);

    // Thanks again globed!
    void setColor(const cocos2d::ccColor3B& color) { m_cursorSprite->setColor(color); }
    const cocos2d::ccColor3B& getColor() { return m_cursorSprite->getColor(); }
    const cocos2d::ccColor3B& getDisplayedColor() { return m_cursorSprite->getDisplayedColor(); }
    GLubyte getDisplayedOpacity() { return m_cursorSprite->getDisplayedOpacity(); }
    GLubyte getOpacity() { return m_cursorSprite->getOpacity(); }
    void setOpacity(GLubyte opacity) { m_cursorSprite->setOpacity(opacity); }
    void setOpacityModifyRGB(bool bValue) { m_cursorSprite->setOpacityModifyRGB(bValue); }
    bool isOpacityModifyRGB() { return m_cursorSprite->isOpacityModifyRGB(); }
    bool isCascadeColorEnabled() { return m_cursorSprite->isCascadeColorEnabled(); }
    void setCascadeColorEnabled(bool cascadeColorEnabled) { m_cursorSprite->setCascadeColorEnabled(cascadeColorEnabled); }
    void updateDisplayedColor(const cocos2d::ccColor3B& color) { m_cursorSprite->updateDisplayedColor(color); }
    bool isCascadeOpacityEnabled() { return m_cursorSprite->isCascadeOpacityEnabled(); }
    void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) { m_cursorSprite->setCascadeOpacityEnabled(cascadeOpacityEnabled); }
    void updateDisplayedOpacity(GLubyte opacity) { m_cursorSprite->updateDisplayedOpacity(opacity); }
    // TrailType m_trail;

    void setVisibleTrail(bool visible) {
        if (this->m_plainTrail) { this->m_plainTrail->setVisible(visible); }
        // if (this->m_ghostTrail) { this->m_ghostTrail->setVisible(visible); }
        // if (this->m_hardTrail) { this->m_hardTrail->setVisible(visible); }
    }

    void createPlainTrail();
    // void createGhostTrail();
    // void createHardTrail();

    void disableAllTrails();


protected:
    bool init(const CursorData& cursorData);
    CursorData m_cursorData;

    Ref<SimplePlayer> m_cursorSprite = nullptr;
    // Ref<CCSprite> m_ohMySog = nullptr;

    Ref<CCMotionStreak> m_plainTrail = nullptr;
    // Ref<GhostTrailEffect> m_ghostTrail = nullptr;
    // Ref<HardStreak> m_hardTrail = nullptr;
};