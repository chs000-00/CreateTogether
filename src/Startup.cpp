#include <Geode/Geode.hpp>
#include <Geode/utils/terminate.hpp>

#include <steamworks/isteammatchmaking.h>
#include <Networking/SteamManager.hpp>
#include <enet.h>
// #include "WindowsStartup.hpp"

using namespace geode::prelude;

// Init_t _Init = nullptr;
// RunFrame_t _RunFrame = nullptr;

$execute {
    #ifdef GEODE_IS_WINDOWS

        auto steam = GetModuleHandle("steam_api64.dll");
        auto steamManager = SteamManager::get();

        #ifdef STEAMWORKS

            if (!steam) {
                geode::log::error("You take 30 million horses and put them in a room, then wait a year. Half of them die due to cramming so you have 15 million left. Some of them have kids so now you have 27 million horses, rinse and repeat. After that, you should be left with 5 of the most beautiful, most inbred creatures on our dear planet earth. Enjoy your creations while they last because they will die. Or you can sell them for major doubloons.");
                geode::log::error("gd pirata. ¡Desactivando Steamworks!");
            } else {
                steamManager->m_isSteamworksLoaded = true;
            }

        #endif

    #endif

    if (enet_initialize () != 0) {
        log::error("enet failed to initialize");

        auto dis = Mod::get()->disable();
        if (!dis) {
            log::error("couldn't disable mod, {}", dis.err());
        }

        geode::utils::terminate("enet failed to initialize");
    }

    // _Init = (Init_t)GetProcAddress(steam, "SteamAPI_ISteamInput_Init");
    // _RunFrame = (RunFrame_t)GetProcAddress(steam, "SteamAPI_ISteamInput_RunFrame");
}

