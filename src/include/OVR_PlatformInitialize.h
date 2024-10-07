// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_PLATFORMINITIALIZE_H
#define OVR_PLATFORMINITIALIZE_H

#include "OVR_Platform_Defs.h"
#include "OVR_PlatformInitializeResult.h"

typedef struct ovrPlatformInitialize *ovrPlatformInitializeHandle;

/// The result of attempting to initialize the platform.
OVRP_PUBLIC_FUNCTION(ovrPlatformInitializeResult) ovr_PlatformInitialize_GetResult(const ovrPlatformInitializeHandle obj);


#endif
