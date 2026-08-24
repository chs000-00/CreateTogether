#pragma once

#define MOD_ID geode::Mod::get()->getID()
#define MOD_VERSION geode::Mod::get()->getVersion().toVString(true)

#define EDITOR_CHANNEL 0
#define CURSOR_CHANNEL 1

#define CHANNEL_COUNT 2

#define DEDICATED_EDITOR_PORT 24018
// #define DEDICATED_CURSOR_PORT 24019

// #define DEDICATED_SERVER_IP 0x7f000001

#define MAX_EDITOR_MESSAGES 128
#define MAX_CURSOR_MESSAGES 64

#define MAX_USERS 8

// Log all received messages
#define LOG_RECV true