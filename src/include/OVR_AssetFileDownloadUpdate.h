// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_ASSETFILEDOWNLOADUPDATE_H
#define OVR_ASSETFILEDOWNLOADUPDATE_H

#include "OVR_Platform_Defs.h"
#include "OVR_Types.h"
#include <stdbool.h>

/// An AssetFileDownloadUpdate represents the download status of an update for
/// an asset file. It contains the asset file ID, the download progress of the
/// update, and its completion status. It can be retrieved using
/// ovrNotification_AssetFile_DownloadUpdate.
typedef struct ovrAssetFileDownloadUpdate *ovrAssetFileDownloadUpdateHandle;

/// \deprecated Use ovr_AssetFileDownloadUpdate_GetAssetId().
OVRP_PUBLIC_FUNCTION(ovrID) ovr_AssetFileDownloadUpdate_GetAssetFileId(const ovrAssetFileDownloadUpdateHandle obj);

/// ID of the asset file. It can be retrieved using
/// ovr_AssetDetails_GetAssetId().
OVRP_PUBLIC_FUNCTION(ovrID) ovr_AssetFileDownloadUpdate_GetAssetId(const ovrAssetFileDownloadUpdateHandle obj);

/// This field is of type uint and represents the total number of bytes in the
/// asset file.
/// \deprecated  Use ovr_AssetFileDownloadUpdate_GetBytesTotalLong() instead.
OVRP_PUBLIC_FUNCTION(unsigned int) ovr_AssetFileDownloadUpdate_GetBytesTotal(const ovrAssetFileDownloadUpdateHandle obj);

/// An integer represents the number of bytes that have been downloaded. -1 If
/// the download hasn't started yet.
/// \deprecated  Use ovr_AssetFileDownloadUpdate_GetBytesTransferredLong() instead.
OVRP_PUBLIC_FUNCTION(int) ovr_AssetFileDownloadUpdate_GetBytesTransferred(const ovrAssetFileDownloadUpdateHandle obj);

/// This field is of type boolean and indicates whether the download has been
/// completed or not.
OVRP_PUBLIC_FUNCTION(bool) ovr_AssetFileDownloadUpdate_GetCompleted(const ovrAssetFileDownloadUpdateHandle obj);

OVRP_PUBLIC_FUNCTION(unsigned long long) ovr_AssetFileDownloadUpdate_GetBytesTotalLong(const ovrAssetFileDownloadUpdateHandle obj);
OVRP_PUBLIC_FUNCTION(long long)          ovr_AssetFileDownloadUpdate_GetBytesTransferredLong(const ovrAssetFileDownloadUpdateHandle obj);

#endif
