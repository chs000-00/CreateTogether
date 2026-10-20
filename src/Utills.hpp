#pragma once

#include <Geode/Geode.hpp>
#include <Geode/binding/GJBaseGameLayer.hpp>
#include <Geode/binding/LevelSettingsObject.hpp>
#include <stacktrace>
#include <steamworks/steamnetworkingtypes.h>
#include <valarray>

using namespace geode::prelude;

using MayFail = Result<void>;
using byte = uint8_t;


// case CTSerialize::MessageBody_ChangeDefaultColor: {
//     SERIALIZE_AND_RECEIVE(ChangeDefaultColor);
//     break;
// }

#define SERIALIZE_AND_RECV(msgType, ...) case CTSerialize::MessageBody_##msgType : { \
    auto GEODE_CONCAT(sarmacro, __LINE__) = PRecv::recv##msgType(static_cast<const CTSerialize::msgType *>(dmsg), ##__VA_ARGS__); \
    if (GEODE_CONCAT(sarmacro, __LINE__).isErr()) return GEODE_CONCAT(sarmacro, __LINE__); \
    break; }

// Checks if a enum is within range.
// Comparison uses <=
bool isWithinRange(int n, int min, int max);

// Toggle stuff in levelSettings based off of an int
Result<void> toggleFromLevelSettings(LevelSettingsObject* settings, int option);

// Change the SteamNetworkingIdentity to a string for hashing, so the cursor code could work properly.
std::string hashSteamNetworkingID(SteamNetworkingIdentity id);

// bool steamworksLoaded();
// bool steamworksUnloaded();

// bool steamworksEnabled();
// bool steamworksDisabled();

std::string convertLobbyResultToString(EResult res);

// template <typename T> struct Ptr {
//     T* inner;

//     T* operator->() const {
//         return inner;
//     }

//     operator T*() {
//         return inner; 
//     }

//     T& Value()
//     {
//         return *inner;
//     }

//     T& operator* ()
//     {
//         return *inner;
//     }

//     bool operator==(T* val) {
//         return this->inner == val;
//     }

//     T* Position()
//     {
//         return inner;
//     }

//     bool operator==(Ptr val) {
//         return this->inner == val;
//     }

//     template <typename U> U as_static() {
//         return static_cast<U>(inner);
//     }

//     template <typename U> U as_dynamic() {
//         return dynamic_cast<U>(inner);
//     }

//     template <typename U> U as_reinterpret() {
//         return reinterpret_cast<U>(inner);
//     }

//     Ptr(T* val) {
//         this->inner = val;
//     }

// private:
//     Ptr() { }
// };