// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_ACHIEVEMENTPROGRESS_H
#define OVR_ACHIEVEMENTPROGRESS_H

#include "OVR_Platform_Defs.h"
#include <stdbool.h>

typedef struct ovrAchievementProgress *ovrAchievementProgressHandle;

/// For bitfield achievements, the current bitfield state.
OVRP_PUBLIC_FUNCTION(const char *) ovr_AchievementProgress_GetBitfield(const ovrAchievementProgressHandle obj);

/// For count achievements, the current counter state.
OVRP_PUBLIC_FUNCTION(unsigned long long) ovr_AchievementProgress_GetCount(const ovrAchievementProgressHandle obj);

/// If the user has already unlocked this achievement.
OVRP_PUBLIC_FUNCTION(bool) ovr_AchievementProgress_GetIsUnlocked(const ovrAchievementProgressHandle obj);

/// The unique string that you use to reference the achievement in your app, as
/// specified in the developer dashboard.
OVRP_PUBLIC_FUNCTION(const char *) ovr_AchievementProgress_GetName(const ovrAchievementProgressHandle obj);

/// If the achievement is unlocked, the time when it was unlocked.
OVRP_PUBLIC_FUNCTION(unsigned long long) ovr_AchievementProgress_GetUnlockTime(const ovrAchievementProgressHandle obj);


#endif
