#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

// I was too lazy to make NetManager a proper CCObject so instead I decided to have this scheduler call it's update functions instead.
class NetworkScheduler : public CCObject {
public:
    void update(float dt);
};