#include "CursorUnit.hpp"
#include "Geode/binding/GameManager.hpp"
#include "Geode/loader/Log.hpp"
#include "Geode/ui/OverlayManager.hpp"
#include "Geode/utils/cocos.hpp"
#include <Geode/binding/GhostTrailEffect.hpp>
#include <Geode/binding/HardStreak.hpp>

using namespace geode::prelude;


// Stolen from globed? lol
CursorUnit* CursorUnit::create(const CursorData& cursorData) {
    auto ret = new CursorUnit();
    if (ret->init(cursorData)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

void CursorUnit::updateCursor(const CursorData& cursorData) {
    auto gameManager = GameManager::get();
    this->m_cursorData = cursorData;
    this->m_cursorSprite->updatePlayerFrame(cursorData.cursorID, IconType::Wave);
    this->m_cursorSprite->setColor(gameManager->colorForIdx(cursorData.cursorColor1));
    this->m_cursorSprite->setSecondColor(gameManager->colorForIdx(cursorData.cursorColor2));

    if (cursorData.cursorHasGlow) {
        this->m_cursorSprite->setGlowOutline(gameManager->colorForIdx(cursorData.cursorGlowColor));
    }
    else {
        this->m_cursorSprite->disableGlowOutline();
    }
}

SimplePlayer* CursorUnit::getSimplePlayer() {
    return this->m_cursorSprite;
}

bool CursorUnit::init(const CursorData& cursorData) {
    if (!CCNode::init()) {
        return false;
    }
    this->m_cursorSprite = SimplePlayer::create(0);
    this->addChild(this->m_cursorSprite);
    this->setZOrder(10067);

    this->setContentSize(this->m_cursorSprite->m_outlineSprite->getScaledContentSize());
    this->m_cursorSprite->setPosition(this->m_cursorSprite->m_outlineSprite->getScaledContentSize() / 2);
    this->updateCursor(cursorData);

    CCScheduler::get()->scheduleUpdateForTarget(this, 5500, false);
    return true;
}

void CursorUnit::createPlainTrail() {
    auto gm = GameManager::get();

    if (this->m_plainTrail) {
        this->m_plainTrail->setVisible(true); 
        auto sprite = "streak_0" + std::to_string(m_cursorData.playerTrail) + "_001.png";
        log::debug("ct loading PlainStreak {}", sprite);
        this->m_plainTrail->setTexture(CCTextureCache::get()->addImage(sprite.c_str(), true));
        // this->m_plainTrail->reset();
        this->m_plainTrail->resumeStroke();
    } else {
        auto sprite = "streak_0" + std::to_string(m_cursorData.playerTrail) + "_001.png";
        log::debug("ct loading PlainStreak {}", sprite);
        // CCTextureCache :skull:
        auto texture = CCTextureCache::get()->addImage(sprite.c_str(), true);
        this->m_plainTrail = CCMotionStreak::create(
            0.3,
            2,
            10,
            ccWHITE,
            texture
        );

        this->m_plainTrail->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });   

        // TODO: TEST THIS OUT!
        this->addChild(this->m_plainTrail);
        this->m_plainTrail->setID("cursor-plain-trail"_spr); 
        this->m_plainTrail->setZOrder(9999);
    }

    if (this->m_cursorData.playerTrail == 6) {
            this->m_plainTrail->enableRepeatMode(0.1);
    } else {
        this->m_plainTrail->m_bRepeatMode = false;
    }

    this->m_plainTrail->m_fMaxSeg = 200.0;
}

void CursorUnit::update(float dt) {
    if(this->m_plainTrail) {
        // I love absolllute (position)
        this->m_plainTrail->setPosition(this->convertToWorldSpace(this->getSimplePlayer()->getPosition()));
    }
}

void CursorUnit::disableAllTrails() {
    if (this->m_plainTrail) { this->m_plainTrail->setVisible(false); }
}
