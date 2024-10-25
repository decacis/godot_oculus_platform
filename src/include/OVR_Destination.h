// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_DESTINATION_H
#define OVR_DESTINATION_H

#include "OVR_Platform_Defs.h"

/// The destination represents where the user would like to go to in the app.
/// It's usually associated with a travel or an invitation. Each destination
/// has ovr_Destination_GetApiName(), ovr_Destination_GetDisplayName(),
/// ovr_Destination_GetDeeplinkMessage() and ovr_Destination_GetShareableUri()
/// link. Please refer to member data documentation for details.
typedef struct ovrDestination *ovrDestinationHandle;

/// You can pass it into ovr_GroupPresenceOptions_SetDestinationApiName when
/// calling ovr_GroupPresence_Set() to set this user's group presence.
OVRP_PUBLIC_FUNCTION(const char *) ovr_Destination_GetApiName(const ovrDestinationHandle obj);

/// The information that will be in ovr_LaunchDetails_GetDeeplinkMessage() when
/// a user enters via a deeplink. Alternatively will be in
/// ovr_User_GetPresenceDeeplinkMessage() if the rich presence is set for the
/// user.
OVRP_PUBLIC_FUNCTION(const char *) ovr_Destination_GetDeeplinkMessage(const ovrDestinationHandle obj);

/// A displayable string of the destination name and it can be retrieved with
/// ovr_Destination_GetDisplayName().
OVRP_PUBLIC_FUNCTION(const char *) ovr_Destination_GetDisplayName(const ovrDestinationHandle obj);

/// A URI that allows the user to deeplink directly to this destination
OVRP_PUBLIC_FUNCTION(const char *) ovr_Destination_GetShareableUri(const ovrDestinationHandle obj);


#endif
