#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/binding/GameObject.hpp>

using namespace geode::prelude;
class $modify(IDLevelEditorLayer, LevelEditorLayer) {

    struct Fields {
        unsigned int m_blocksPlaced = 0;

        Ref<CCDictionary> m_pUniqueIDOfGameObject = nullptr;
    };

    
    // GameObject* createObject(int p0, cocos2d::CCPoint p1, bool p2);
    // // void updateLevelFont(int p0);
    // bool init(GJGameLevel* p0, bool p1);
    // void deleteObject(GameObject* obj);
    // // void addToGroup(GameObject* p0, int p1, bool p2);
    // // void removeFromGroup(GameObject* p0, int p1);
};