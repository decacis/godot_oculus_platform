// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_ACHIEVEMENTUPDATE_H
#define OVR_ACHIEVEMENTUPDATE_H

#include "OVR_Platform_Defs.h"
#include <stdbool.h>

typedef struct ovrAchievementUpdate *ovrAchievementUpdateHandle;

/// This indicates if this update caused the achievement to unlock.
OVRP_PUBLIC_FUNCTION(bool) ovr_AchievementUpdate_GetJustUnlocked(const ovrAchievementUpdateHandle obj);

/// The unique ovr_AchievementDefinition_GetName() used to reference the
/// updated achievement.
OVRP_PUBLIC_FUNCTION(const char *) ovr_AchievementUpdate_GetName(const ovrAchievementUpdateHandle obj);


#endif
