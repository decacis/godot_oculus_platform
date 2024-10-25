// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_APPLICATION_OPTIONS_H
#define OVR_APPLICATION_OPTIONS_H

#include "OVR_Platform_Defs.h"
#include "OVR_Types.h"
#include <stddef.h>
#include <stdbool.h>


struct ovrApplicationOptions;
/// The Application option contains additional configuration to be passed in to
/// ovr_Application_LaunchOtherApp() and
/// ovr_Application_InstallAppUpdateAndRelaunch(). It contains 5 fields
/// ovr_ApplicationOptions_SetDeeplinkMessage,
/// ovr_ApplicationOptions_SetDestinationApiName,
/// ovr_ApplicationOptions_SetLobbySessionId,
/// ovr_ApplicationOptions_SetMatchSessionId and
/// ovr_ApplicationOptions_SetRoomId.
typedef struct ovrApplicationOptions* ovrApplicationOptionsHandle;
/// \brief Creates a new instance of ovrApplicationOptionsHandle() which is used to customize the option flow. It returns a handle to the newly created options object, which can be used to set various properties for the options.
OVRP_PUBLIC_FUNCTION(ovrApplicationOptionsHandle) ovr_ApplicationOptions_Create();
/// \brief Destroys an existing instance of the ovrApplicationOptionsHandle() and frees up memory when you're done using it.
OVRP_PUBLIC_FUNCTION(void) ovr_ApplicationOptions_Destroy(ovrApplicationOptionsHandle handle);
/// A message to be passed to a launched app, which can be retrieved with
/// ovr_LaunchDetails_GetDeeplinkMessage().
OVRP_PUBLIC_FUNCTION(void) ovr_ApplicationOptions_SetDeeplinkMessage(ovrApplicationOptionsHandle handle, const char * value);
/// If provided, the intended destination to be passed to the launched app,
/// which can be retrieved with ovr_LaunchDetails_GetDestinationApiName().
OVRP_PUBLIC_FUNCTION(void) ovr_ApplicationOptions_SetDestinationApiName(ovrApplicationOptionsHandle handle, const char * value);
/// If provided, the intended lobby where the launched app should take the
/// user. All users with the same lobby_session_id should end up grouped
/// together in the launched app, which can be retrieved with
/// ovr_LaunchDetails_GetLobbySessionID().
OVRP_PUBLIC_FUNCTION(void) ovr_ApplicationOptions_SetLobbySessionId(ovrApplicationOptionsHandle handle, const char * value);
/// If provided, the intended instance of the destination that a user should be
/// launched into, which can be retrieved with
/// ovr_LaunchDetails_GetMatchSessionID().
OVRP_PUBLIC_FUNCTION(void) ovr_ApplicationOptions_SetMatchSessionId(ovrApplicationOptionsHandle handle, const char * value);
/// [Deprecated]If provided, the intended room where the launched app should
/// take the user (all users heading to the same place should have the same
/// value). A room_id of 0 is INVALID.
OVRP_PUBLIC_FUNCTION(void) ovr_ApplicationOptions_SetRoomId(ovrApplicationOptionsHandle handle, ovrID value);

#endif
