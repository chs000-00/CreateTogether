#include "NetworkScheduler.hpp"
#include <Networking/NetManager.hpp>


$execute {
    log::info("Creating CT NetworkScheduler!");
    Loader::get()->queueInMainThread([]{
        CCScheduler::get()->scheduleUpdateForTarget(new NetworkScheduler{}, 3200, false);
    });
}

void NetworkScheduler::update(float dt) {
    NetManager::get()->update();
}