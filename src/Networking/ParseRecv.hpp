#pragma once

#include <Geode/Geode.hpp>
#include <Networking/NetManager.hpp>
#include <Types/vUIDContainer.hpp>
#include <Utills.hpp>
#include <flatbuffers/flatbuffers.h>
#include <ctserialize_generated.h>


namespace PRecv {

    MayFail recvCreateObjects(const CTSerialize::CreateObjects* msg);

    MayFail recvDeleteObjects(const CTSerialize::DeleteObjects* msg);

    MayFail recvMoveObjects(const CTSerialize::MoveObjects* msg);

    MayFail recvLevelSettingChange(const CTSerialize::LevelSettingChange* msg);

    MayFail recvRotateObjects(const CTSerialize::RotateObjects* msg);

    MayFail recvPasteObjects(const CTSerialize::PasteObjects* msg);

    MayFail recvModifyObjects(const CTSerialize::ModifyObjects* msg);

    MayFail recvChangeDefaultColor(const CTSerialize::ChangeDefaultColor* msg);

    MayFail recvRequestLevel(const CTSerialize::RequestLevel* msg);

    MayFail recvReturnLevelString(const CTSerialize::ReturnLevelString* msg);

    MayFail recvUpdateSong(const CTSerialize::UpdateSong* msg);

    MayFail recvChangeArt(const CTSerialize::ChangeArt* msg);

    MayFail recvSpeedChange(const CTSerialize::SpeedChange* msg);

    MayFail recvGameModeChange(const CTSerialize::GameModeChange* msg);

    MayFail recvPlayerCursorData(const CTSerialize::PlayerCursorData* msg);

    MayFail recvRequestForCursors(const CTSerialize::RequestForCursors* msg);

}