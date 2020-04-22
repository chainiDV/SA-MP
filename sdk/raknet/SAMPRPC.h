
#ifndef _SAMPRPC_H
#define _SAMPRPC_H

enum eRPCTable
{
	RPC_ServerJoin,
	RPC_ServerQuit,
	RPC_InitGame,
	RPC_VehicleSpawn,
	RPC_VehicleDestroy,
	RPC_SetCheckpoint,
	RPC_DisableCheckpoint,
	RPC_SetRaceCheckpoint,
	RPC_DisableRaceCheckpoint,
	RPC_GameModeRestart,
	RPC_ConnectionRejected,
	RPC_ClientMessage,
	RPC_WorldTime,
	RPC_Pickup,
	RPC_DestroyPickup,
	RPC_DestroyWeaponPickup,
	RPC_Weather,
	RPC_Instagib,
	RPC_SetTimeEx,
	RPC_ToggleClock,
	RPC_Chat,
	RPC_RequestClass,
	RPC_RequestSpawn,
	RPC_Spawn,
	RPC_Death,
	RPC_EnterVehicle,
	RPC_ExitVehicle,
	RPC_UpdateScoresPingsIPs,
	RPC_SvrStats,
	RPC_ScmEvent,
	RPC_ScrSetSpawnInfo,
	RPC_ScrSetPlayerTeam,
	RPC_ScrSetPlayerSkin,
	RPC_ScrSetPlayerName,
	RPC_ScrSetPlayerPos,
	RPC_ScrSetPlayerPosFindZ,
	RPC_ScrSetPlayerHealth,
	RPC_ScrPutPlayerInVehicle,
	RPC_ScrRemovePlayerFromVehicle,
	RPC_ScrSetPlayerColor,
	RPC_ScrDisplayGameText,
	RPC_ScrSetInterior,
	RPC_ScrSetCameraPos,
	RPC_ScrSetCameraLookAt,
	RPC_ScrSetVehiclePos,
	RPC_ScrSetVehicleZAngle,
	RPC_ScrVehicleParams,
	RPC_ScrSetCameraBehindPlayer,
	RPC_ScrTogglePlayerControllable,
	RPC_ScrPlaySound,
	RPC_ScrSetWorldBounds,
	RPC_ScrHaveSomeMoney,
	RPC_ScrSetPlayerFacingAngle,
	RPC_ScrResetMoney,
	RPC_ScrResetPlayerWeapons,
	RPC_ScrGivePlayerWeapon,
	RPC_ScrRespawnVehicle,
	RPC_ScrLinkVehicle,
	RPC_ScrSetPlayerArmour,
	RPC_ScrDeathMessage,
	RPC_ScrSetMapIcon,
	RPC_ScrDisableMapIcon,
	RPC_ScrSetWeaponAmmo,
	RPC_ScrSetGravity,
	RPC_ScrSetVehicleHealth,
	RPC_ScrAttachTrailerToVehicle,
	RPC_ScrDetachTrailerFromVehicle,
	RPC_ScrCreateObject,
	RPC_ScrSetObjectPos,
	RPC_ScrSetObjectRotation,
	RPC_ScrDestroyObject,
	RPC_ScrSetPlayerVirtualWorld,
	RPC_ScrSetVehicleVirtualWorld,
	RPC_ScrCreateExplosion,
	RPC_ScrShowNameTag,
	RPC_ScrMoveObject,
	RPC_ScrStopObject,
	RPC_ScrNumberPlate,
	RPC_ScrTogglePlayerSpectating,
	RPC_ScrSetPlayerSpectating,
	RPC_ScrPlayerSpectatePlayer,
	RPC_ScrPlayerSpectateVehicle,
	RPC_ScrForceSpawnSelection,
	RPC_ScrRemoveComponent,
	RPC_ScrAttachObjectToPlayer,
	RPC_ScrInitMenu,
	RPC_ScrShowMenu,
	RPC_ScrHideMenu,
	RPC_ScrSetPlayerWantedLevel,
	RPC_ScrShowTextDraw,
	RPC_ScrHideTextDraw,
	RPC_ScrEditTextDraw,
	RPC_ScrAddGangZone,
	RPC_ScrRemoveGangZone,
	RPC_ScrFlashGangZone,
	RPC_ScrStopFlashGangZone,
	RPC_ScrApplyAnimation,
	RPC_ScrClearAnimations,
	RPC_ScrSetSpecialAction,
	RPC_ScrEnableStuntBonus,
	RPC_ScrSetVehicle,
	RPC_ScrSetPlayer,
	RPC_ScrVehicleVelocity,
	RPC_ScrPlayerVelocity,
	RPC_ClientJoin,
	RPC_ServerCommand,
	RPC_SetInteriorId,
	RPC_AdminMapTeleport,
	RPC_VehicleDestroyed,
	RPC_PickedUpWeapon,
	RPC_PickedUpPickup,
	RPC_MenuSelect,
	RPC_MenuQuit,
	RPC_RconConnect,
	RPC_RconCommand,
	RPC_RconEvent,
	RPC_RconPlayerInfo,
	RPC_ACAuthRequest,
	RPC_ACAuthResponse,
	RPC_ACAuthEngineLoaded,
	RPC_ACServerProtected,
	RPC_ScrInterpolateCamera,
	RPC_TypingEvent,
	RPC_ScrVehicleComponent,

	MAX_RPC_ID_AVAILABLE
};

#endif // _SAMPRPC_H
