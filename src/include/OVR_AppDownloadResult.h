// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_APPDOWNLOADRESULT_H
#define OVR_APPDOWNLOADRESULT_H

#include "OVR_Platform_Defs.h"
#include "OVR_AppInstallResult.h"

typedef struct ovrAppDownloadResult *ovrAppDownloadResultHandle;

/// Result of the download or install operation returned by the installer
OVRP_PUBLIC_FUNCTION(ovrAppInstallResult) ovr_AppDownloadResult_GetAppInstallResult(const ovrAppDownloadResultHandle obj);

/// Timestamp in milliseconds when the operation finished.
OVRP_PUBLIC_FUNCTION(long long) ovr_AppDownloadResult_GetTimestamp(const ovrAppDownloadResultHandle obj);


#endif
