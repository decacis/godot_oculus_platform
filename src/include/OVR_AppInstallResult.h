// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_APP_INSTALL_RESULT_H
#define OVR_APP_INSTALL_RESULT_H

#include "OVR_Platform_Defs.h"

typedef enum ovrAppInstallResult_ {
  ovrAppInstallResult_Unknown,
  ovrAppInstallResult_LowStorage,
  ovrAppInstallResult_NetworkError,
  ovrAppInstallResult_DuplicateRequest,
  ovrAppInstallResult_InstallerError,
  ovrAppInstallResult_UserCancelled,
  ovrAppInstallResult_AuthorizationError,
  ovrAppInstallResult_Success,
} ovrAppInstallResult;

/// Converts an ovrAppInstallResult enum value to a string
/// The returned string does not need to be freed
OVRPL_PUBLIC_FUNCTION(const char*) ovrAppInstallResult_ToString(ovrAppInstallResult value);

/// Converts a string representing an ovrAppInstallResult enum value to an enum value
///
OVRPL_PUBLIC_FUNCTION(ovrAppInstallResult) ovrAppInstallResult_FromString(const char* str);

#endif
