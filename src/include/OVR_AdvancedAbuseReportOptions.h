// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_ADVANCED_ABUSE_REPORT_OPTIONS_H
#define OVR_ADVANCED_ABUSE_REPORT_OPTIONS_H

#include "OVR_Platform_Defs.h"
#include "OVR_Types.h"
#include <stddef.h>
#include <stdbool.h>

#include "OVR_AbuseReportType.h"
#include "OVR_AbuseReportVideoMode.h"

struct ovrAdvancedAbuseReportOptions;
typedef struct ovrAdvancedAbuseReportOptions* ovrAdvancedAbuseReportOptionsHandle;

OVRP_PUBLIC_FUNCTION(ovrAdvancedAbuseReportOptionsHandle) ovr_AdvancedAbuseReportOptions_Create();
OVRP_PUBLIC_FUNCTION(void) ovr_AdvancedAbuseReportOptions_Destroy(ovrAdvancedAbuseReportOptionsHandle handle);
/// This field is intended to allow developers to pass custom metadata through
/// the report flow. The metadata passed through is included with the report
/// received by the developer.
OVRP_PUBLIC_FUNCTION(void) ovr_AdvancedAbuseReportOptions_SetDeveloperDefinedContextString(ovrAdvancedAbuseReportOptionsHandle handle, const char* key, const char* value);
OVRP_PUBLIC_FUNCTION(void) ovr_AdvancedAbuseReportOptions_ClearDeveloperDefinedContext(ovrAdvancedAbuseReportOptionsHandle handle);
/// If report_type is object/content, a string representing the type of content
/// being reported. This should correspond to the object_type string used in
/// the UI
OVRP_PUBLIC_FUNCTION(void) ovr_AdvancedAbuseReportOptions_SetObjectType(ovrAdvancedAbuseReportOptionsHandle handle, const char * value);
/// The intended entity being reported, whether user or object/content.
OVRP_PUBLIC_FUNCTION(void) ovr_AdvancedAbuseReportOptions_SetReportType(ovrAdvancedAbuseReportOptionsHandle handle, ovrAbuseReportType value);
/// Provide a list of users to suggest for reporting. This list should include
/// users that the reporter has recently interacted with to aid them in
/// selecting the right user to report.
OVRP_PUBLIC_FUNCTION(void) ovr_AdvancedAbuseReportOptions_AddSuggestedUser(ovrAdvancedAbuseReportOptionsHandle handle, ovrID value);
OVRP_PUBLIC_FUNCTION(void) ovr_AdvancedAbuseReportOptions_ClearSuggestedUsers(ovrAdvancedAbuseReportOptionsHandle handle);
/// The video mode controls whether or not the abuse report flow should collect
/// evidence and whether it is optional or not. "Collect" requires video
/// evidence to be provided by the user. "Optional" presents the user with the
/// option to provide video evidence. "Skip" bypasses the video evidence
/// collection step altogether.
OVRP_PUBLIC_FUNCTION(void) ovr_AdvancedAbuseReportOptions_SetVideoMode(ovrAdvancedAbuseReportOptionsHandle handle, ovrAbuseReportVideoMode value);

#endif
