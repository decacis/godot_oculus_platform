// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_CHALLENGE_H
#define OVR_CHALLENGE_H

#include "OVR_Platform_Defs.h"
#include "OVR_ChallengeCreationType.h"
#include "OVR_ChallengeVisibility.h"
#include "OVR_Leaderboard.h"
#include "OVR_Types.h"
#include "OVR_UserArray.h"

typedef struct ovrChallenge *ovrChallengeHandle;

/// An enum that specifies if this challenge was created by a user
/// (ovrChallengeCreationType_UserCreated) or the app developer
/// (ovrChallengeCreationType_DeveloperCreated).
OVRP_PUBLIC_FUNCTION(ovrChallengeCreationType) ovr_Challenge_GetCreationType(const ovrChallengeHandle obj);

/// A displayable string of the challenge's description.
OVRP_PUBLIC_FUNCTION(const char *) ovr_Challenge_GetDescription(const ovrChallengeHandle obj);

/// The timestamp when this challenge ends.
OVRP_PUBLIC_FUNCTION(unsigned long long) ovr_Challenge_GetEndDate(const ovrChallengeHandle obj);

/// Users that are invited to this challenge.
/// This method may return null. This indicates that the value is not present or that the curent
/// app or user is not permitted to access it.
OVRP_PUBLIC_FUNCTION(ovrUserArrayHandle) ovr_Challenge_GetInvitedUsers(const ovrChallengeHandle obj);

/// The ovrLeaderboardHandle associated with this challenge.
OVRP_PUBLIC_FUNCTION(ovrLeaderboardHandle) ovr_Challenge_GetLeaderboard(const ovrChallengeHandle obj);

/// Users that have participated in this challenge.
/// This method may return null. This indicates that the value is not present or that the curent
/// app or user is not permitted to access it.
OVRP_PUBLIC_FUNCTION(ovrUserArrayHandle) ovr_Challenge_GetParticipants(const ovrChallengeHandle obj);

/// The timestamp when this challenge begins.
OVRP_PUBLIC_FUNCTION(unsigned long long) ovr_Challenge_GetStartDate(const ovrChallengeHandle obj);

/// A displayable string of the challenge's title.
OVRP_PUBLIC_FUNCTION(const char *) ovr_Challenge_GetTitle(const ovrChallengeHandle obj);

/// An enum that specifies who can see and participate in this challenge.
///
/// ovrChallengeVisibility_InviteOnly - Only those invited can participate in
/// it. Everyone can see it.
///
/// ovrChallengeVisibility_Public - Everyone can participate and see this
/// challenge.
///
/// ovrChallengeVisibility_Private - Only those invited can participate and see
/// this challenge.
OVRP_PUBLIC_FUNCTION(ovrChallengeVisibility) ovr_Challenge_GetVisibility(const ovrChallengeHandle obj);

OVRP_PUBLIC_FUNCTION(ovrID) ovr_Challenge_GetID(const ovrChallengeHandle obj);

#endif
