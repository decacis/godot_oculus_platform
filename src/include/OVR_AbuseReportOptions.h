// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_ABUSE_REPORT_OPTIONS_H
#define OVR_ABUSE_REPORT_OPTIONS_H

#include "OVR_Platform_Defs.h"
#include "OVR_Types.h"
#include <stddef.h>
#include <stdbool.h>

#include "OVR_AbuseReportType.h"

struct ovrAbuseReportOptions;
typedef struct ovrAbuseReportOptions* ovrAbuseReportOptionsHandle;

OVRP_PUBLIC_FUNCTION(ovrAbuseReportOptionsHandle) ovr_AbuseReportOptions_Create();
OVRP_PUBLIC_FUNCTION(void) ovr_AbuseReportOptions_Destroy(ovrAbuseReportOptionsHandle handle);
/// Set whether or not to show the user selection step in the report dialog.
OVRP_PUBLIC_FUNCTION(void) ovr_AbuseReportOptions_SetPreventPeopleChooser(ovrAbuseReportOptionsHandle handle, bool value);
/// The intended entity being reported, whether user or object/content.
OVRP_PUBLIC_FUNCTION(void) ovr_AbuseReportOptions_SetReportType(ovrAbuseReportOptionsHandle handle, ovrAbuseReportType value);

#endif
