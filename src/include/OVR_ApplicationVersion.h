// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_APPLICATIONVERSION_H
#define OVR_APPLICATIONVERSION_H

#include "OVR_Platform_Defs.h"

typedef struct ovrApplicationVersion *ovrApplicationVersionHandle;

/// Version code number for the version of the application currently installed
/// on the device.
OVRP_PUBLIC_FUNCTION(int) ovr_ApplicationVersion_GetCurrentCode(const ovrApplicationVersionHandle obj);

/// Version name string for the version of the application currently installed
/// on the device.
OVRP_PUBLIC_FUNCTION(const char *) ovr_ApplicationVersion_GetCurrentName(const ovrApplicationVersionHandle obj);

/// Version code number of the latest update of the application. This may or
/// may not be currently installed on the device.
OVRP_PUBLIC_FUNCTION(int) ovr_ApplicationVersion_GetLatestCode(const ovrApplicationVersionHandle obj);

/// Version name string of the latest update of the application. This may or
/// may not be currently installed on the device.
OVRP_PUBLIC_FUNCTION(const char *) ovr_ApplicationVersion_GetLatestName(const ovrApplicationVersionHandle obj);

/// Seconds since epoch when the latest application update was released.
OVRP_PUBLIC_FUNCTION(long long) ovr_ApplicationVersion_GetReleaseDate(const ovrApplicationVersionHandle obj);

/// Size of the latest application update in bytes.
OVRP_PUBLIC_FUNCTION(const char *) ovr_ApplicationVersion_GetSize(const ovrApplicationVersionHandle obj);


#endif
