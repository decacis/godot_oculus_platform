// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_LEADERBOARDENTRY_H
#define OVR_LEADERBOARDENTRY_H

#include "OVR_Platform_Defs.h"
#include "OVR_SupplementaryMetric.h"
#include "OVR_Types.h"
#include "OVR_User.h"

typedef struct ovrLeaderboardEntry *ovrLeaderboardEntryHandle;

/// The score displayed in the leaderboard of this entry.
OVRP_PUBLIC_FUNCTION(const char *) ovr_LeaderboardEntry_GetDisplayScore(const ovrLeaderboardEntryHandle obj);

/// A 2KB custom data field that is associated with the leaderboard entry. This
/// can be a game replay or anything that provides more detail about the entry
/// to the viewer. It will be used by two entry methods:
/// ovr_Leaderboard_WriteEntry() and
/// ovr_Leaderboard_WriteEntryWithSupplementaryMetric()
OVRP_PUBLIC_FUNCTION(const char *) ovr_LeaderboardEntry_GetExtraData(const ovrLeaderboardEntryHandle obj);

/// The ID of this leaderboard entry.
OVRP_PUBLIC_FUNCTION(ovrID) ovr_LeaderboardEntry_GetID(const ovrLeaderboardEntryHandle obj);

/// The rank of this leaderboard entry in the leaderboard.
OVRP_PUBLIC_FUNCTION(int) ovr_LeaderboardEntry_GetRank(const ovrLeaderboardEntryHandle obj);

/// The raw underlying value of the leaderboard entry score.
OVRP_PUBLIC_FUNCTION(long long) ovr_LeaderboardEntry_GetScore(const ovrLeaderboardEntryHandle obj);

/// A metric that can be used for tiebreakers by
/// ovr_Leaderboard_WriteEntryWithSupplementaryMetric().
/// This method may return null. This indicates that the value is not present or that the curent
/// app or user is not permitted to access it.
OVRP_PUBLIC_FUNCTION(ovrSupplementaryMetricHandle) ovr_LeaderboardEntry_GetSupplementaryMetric(const ovrLeaderboardEntryHandle obj);

/// The timestamp of this entry being created in the leaderboard.
OVRP_PUBLIC_FUNCTION(unsigned long long) ovr_LeaderboardEntry_GetTimestamp(const ovrLeaderboardEntryHandle obj);

/// User of this leaderboard entry.
OVRP_PUBLIC_FUNCTION(ovrUserHandle) ovr_LeaderboardEntry_GetUser(const ovrLeaderboardEntryHandle obj);

OVRP_PUBLIC_FUNCTION(unsigned int) ovr_LeaderboardEntry_GetExtraDataLength(const ovrLeaderboardEntryHandle obj);

#endif
