// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_CHALLENGE_OPTIONS_H
#define OVR_CHALLENGE_OPTIONS_H

#include "OVR_Platform_Defs.h"
#include "OVR_Types.h"
#include <stddef.h>
#include <stdbool.h>

#include "OVR_ChallengeViewerFilter.h"
#include "OVR_ChallengeVisibility.h"

struct ovrChallengeOptions;
typedef struct ovrChallengeOptions* ovrChallengeOptionsHandle;

OVRP_PUBLIC_FUNCTION(ovrChallengeOptionsHandle) ovr_ChallengeOptions_Create();
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_Destroy(ovrChallengeOptionsHandle handle);
/// The description of the challenge that can be retrieved with
/// ovr_Challenge_GetDescription().
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetDescription(ovrChallengeOptionsHandle handle, const char * value);
/// The timestamp when this challenge ends which can be retrieved with
/// ovr_Challenge_GetEndDate().
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetEndDate(ovrChallengeOptionsHandle handle, unsigned long long value);
/// This indicates whether to include challenges that are currently active.
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetIncludeActiveChallenges(ovrChallengeOptionsHandle handle, bool value);
/// This indicates whether to include challenges that have not yet started.
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetIncludeFutureChallenges(ovrChallengeOptionsHandle handle, bool value);
/// This indicates whether to include challenges that have already ended.
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetIncludePastChallenges(ovrChallengeOptionsHandle handle, bool value);
/// Optional: Only find challenges belonging to this leaderboard.
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetLeaderboardName(ovrChallengeOptionsHandle handle, const char * value);
/// The timestamp when this challenge starts which can be retrieved with
/// ovr_Challenge_GetStartDate().
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetStartDate(ovrChallengeOptionsHandle handle, unsigned long long value);
/// The title of the challenge that can be retrieved with
/// ovr_Challenge_GetTitle().
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetTitle(ovrChallengeOptionsHandle handle, const char * value);
/// An enum that specifies what filter to apply to the list of returned
/// challenges.
///
/// Returns all public ((ovrChallengeVisibility_Public)) and invite-only
/// (ovrChallengeVisibility_InviteOnly) ovrChallengeHandles in which the user
/// is a participant or invitee. Excludes private
/// (ovrChallengeVisibility_Private) challenges.
///
/// ovrChallengeViewerFilter_Participating - Returns challenges the user is
/// participating in.
///
/// ovrChallengeViewerFilter_Invited - Returns challenges the user is invited
/// to.
///
/// ovrChallengeViewerFilter_ParticipatingOrInvited - Returns challenges the
/// user is either participating in or invited to.
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetViewerFilter(ovrChallengeOptionsHandle handle, ovrChallengeViewerFilter value);
/// Specifies who can see and participate in this challenge. It can be
/// retrieved with ovr_Challenge_GetVisibility().
OVRP_PUBLIC_FUNCTION(void) ovr_ChallengeOptions_SetVisibility(ovrChallengeOptionsHandle handle, ovrChallengeVisibility value);

#endif
