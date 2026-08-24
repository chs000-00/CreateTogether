#include "NetworkScheduler.hpp"
#include <Networking/NetManager.hpp>


$execute {
    log::debug("Creating CT NetworkScheduler!");
    Loader::get()->queueInMainThread([]{
        CCScheduler::get()->scheduleUpdateForTarget(new NetworkScheduler{}, 3200, false);
        log::debug("CT NetworkScheduler scheduled.");
    });
}

void NetworkScheduler::update(float dt) {
    NetManager::get()->update();
}