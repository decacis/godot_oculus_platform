// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#ifndef OVR_MESSAGE_H
#define OVR_MESSAGE_H

#include "OVR_Platform_Defs.h"
#include "OVR_AbuseReportRecording.h"
#include "OVR_AchievementDefinitionArray.h"
#include "OVR_AchievementProgressArray.h"
#include "OVR_AchievementUpdate.h"
#include "OVR_AppDownloadProgressResult.h"
#include "OVR_AppDownloadResult.h"
#include "OVR_ApplicationInviteArray.h"
#include "OVR_ApplicationVersion.h"
#include "OVR_AssetDetails.h"
#include "OVR_AssetDetailsArray.h"
#include "OVR_AssetFileDeleteResult.h"
#include "OVR_AssetFileDownloadCancelResult.h"
#include "OVR_AssetFileDownloadResult.h"
#include "OVR_AssetFileDownloadUpdate.h"
#include "OVR_AvatarEditorResult.h"
#include "OVR_BlockedUserArray.h"
#include "OVR_Challenge.h"
#include "OVR_ChallengeArray.h"
#include "OVR_ChallengeEntryArray.h"
#include "OVR_CowatchingState.h"
#include "OVR_CowatchViewerArray.h"
#include "OVR_CowatchViewerUpdate.h"
#include "OVR_DataStore.h"
#include "OVR_DestinationArray.h"
#include "OVR_Error.h"
#include "OVR_GroupPresenceJoinIntent.h"
#include "OVR_GroupPresenceLeaveIntent.h"
#include "OVR_HttpTransferUpdate.h"
#include "OVR_InstalledApplicationArray.h"
#include "OVR_InvitePanelResultInfo.h"
#include "OVR_LaunchBlockFlowResult.h"
#include "OVR_LaunchFriendRequestFlowResult.h"
#include "OVR_LaunchInvitePanelFlowResult.h"
#include "OVR_LaunchReportFlowResult.h"
#include "OVR_LaunchUnblockFlowResult.h"
#include "OVR_LeaderboardArray.h"
#include "OVR_LeaderboardEntryArray.h"
#include "OVR_LeaderboardUpdateStatus.h"
#include "OVR_LinkedAccountArray.h"
#include "OVR_LivestreamingApplicationStatus.h"
#include "OVR_LivestreamingStartResult.h"
#include "OVR_LivestreamingStatus.h"
#include "OVR_LivestreamingVideoStats.h"
#include "OVR_MessageType.h"
#include "OVR_MicrophoneAvailabilityState.h"
#include "OVR_NetSyncConnection.h"
#include "OVR_NetSyncSessionArray.h"
#include "OVR_NetSyncSessionsChangedNotification.h"
#include "OVR_NetSyncSetSessionPropertyResult.h"
#include "OVR_NetSyncVoipAttenuationValueArray.h"
#include "OVR_OrgScopedID.h"
#include "OVR_Party.h"
#include "OVR_PartyID.h"
#include "OVR_PartyUpdateNotification.h"
#include "OVR_PidArray.h"
#include "OVR_PlatformInitialize.h"
#include "OVR_ProductArray.h"
#include "OVR_Purchase.h"
#include "OVR_PurchaseArray.h"
#include "OVR_RejoinDialogResult.h"
#include "OVR_SdkAccountArray.h"
#include "OVR_SendInvitesResult.h"
#include "OVR_ShareMediaResult.h"
#include "OVR_SystemVoipState.h"
#include "OVR_Types.h"
#include "OVR_User.h"
#include "OVR_UserAccountAgeCategory.h"
#include "OVR_UserArray.h"
#include "OVR_UserCapabilityArray.h"
#include "OVR_UserDataStoreUpdateResponse.h"
#include "OVR_UserProof.h"
#include "OVR_UserReportID.h"
#include <stdbool.h>

typedef struct ovrMessage *ovrMessageHandle;

OVRP_PUBLIC_FUNCTION(ovrAbuseReportRecordingHandle)               ovr_Message_GetAbuseReportRecording(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAchievementDefinitionArrayHandle)         ovr_Message_GetAchievementDefinitionArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAchievementProgressArrayHandle)           ovr_Message_GetAchievementProgressArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAchievementUpdateHandle)                  ovr_Message_GetAchievementUpdate(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAppDownloadProgressResultHandle)          ovr_Message_GetAppDownloadProgressResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAppDownloadResultHandle)                  ovr_Message_GetAppDownloadResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrApplicationInviteArrayHandle)             ovr_Message_GetApplicationInviteArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrApplicationVersionHandle)                 ovr_Message_GetApplicationVersion(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAssetDetailsHandle)                       ovr_Message_GetAssetDetails(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAssetDetailsArrayHandle)                  ovr_Message_GetAssetDetailsArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAssetFileDeleteResultHandle)              ovr_Message_GetAssetFileDeleteResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAssetFileDownloadCancelResultHandle)      ovr_Message_GetAssetFileDownloadCancelResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAssetFileDownloadResultHandle)            ovr_Message_GetAssetFileDownloadResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAssetFileDownloadUpdateHandle)            ovr_Message_GetAssetFileDownloadUpdate(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrAvatarEditorResultHandle)                 ovr_Message_GetAvatarEditorResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrBlockedUserArrayHandle)                   ovr_Message_GetBlockedUserArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrChallengeHandle)                          ovr_Message_GetChallenge(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrChallengeArrayHandle)                     ovr_Message_GetChallengeArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrChallengeEntryArrayHandle)                ovr_Message_GetChallengeEntryArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrCowatchViewerArrayHandle)                 ovr_Message_GetCowatchViewerArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrCowatchViewerUpdateHandle)                ovr_Message_GetCowatchViewerUpdate(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrCowatchingStateHandle)                    ovr_Message_GetCowatchingState(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrDataStoreHandle)                          ovr_Message_GetDataStore(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrDestinationArrayHandle)                   ovr_Message_GetDestinationArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrErrorHandle)                              ovr_Message_GetError(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrGroupPresenceJoinIntentHandle)            ovr_Message_GetGroupPresenceJoinIntent(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrGroupPresenceLeaveIntentHandle)           ovr_Message_GetGroupPresenceLeaveIntent(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrHttpTransferUpdateHandle)                 ovr_Message_GetHttpTransferUpdate(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrInstalledApplicationArrayHandle)          ovr_Message_GetInstalledApplicationArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrInvitePanelResultInfoHandle)              ovr_Message_GetInvitePanelResultInfo(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLaunchBlockFlowResultHandle)              ovr_Message_GetLaunchBlockFlowResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLaunchFriendRequestFlowResultHandle)      ovr_Message_GetLaunchFriendRequestFlowResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLaunchInvitePanelFlowResultHandle)        ovr_Message_GetLaunchInvitePanelFlowResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLaunchReportFlowResultHandle)             ovr_Message_GetLaunchReportFlowResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLaunchUnblockFlowResultHandle)            ovr_Message_GetLaunchUnblockFlowResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLeaderboardArrayHandle)                   ovr_Message_GetLeaderboardArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLeaderboardEntryArrayHandle)              ovr_Message_GetLeaderboardEntryArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLeaderboardUpdateStatusHandle)            ovr_Message_GetLeaderboardUpdateStatus(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLinkedAccountArrayHandle)                 ovr_Message_GetLinkedAccountArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLivestreamingApplicationStatusHandle)     ovr_Message_GetLivestreamingApplicationStatus(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLivestreamingStartResultHandle)           ovr_Message_GetLivestreamingStartResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLivestreamingStatusHandle)                ovr_Message_GetLivestreamingStatus(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrLivestreamingVideoStatsHandle)            ovr_Message_GetLivestreamingVideoStats(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrMicrophoneAvailabilityStateHandle)        ovr_Message_GetMicrophoneAvailabilityState(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrMessageHandle)                            ovr_Message_GetNativeMessage(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrNetSyncConnectionHandle)                  ovr_Message_GetNetSyncConnection(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrNetSyncSessionArrayHandle)                ovr_Message_GetNetSyncSessionArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrNetSyncSessionsChangedNotificationHandle) ovr_Message_GetNetSyncSessionsChangedNotification(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrNetSyncSetSessionPropertyResultHandle)    ovr_Message_GetNetSyncSetSessionPropertyResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrNetSyncVoipAttenuationValueArrayHandle)   ovr_Message_GetNetSyncVoipAttenuationValueArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrOrgScopedIDHandle)                        ovr_Message_GetOrgScopedID(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrPartyHandle)                              ovr_Message_GetParty(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrPartyIDHandle)                            ovr_Message_GetPartyID(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrPartyUpdateNotificationHandle)            ovr_Message_GetPartyUpdateNotification(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrPidArrayHandle)                           ovr_Message_GetPidArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrPlatformInitializeHandle)                 ovr_Message_GetPlatformInitialize(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrProductArrayHandle)                       ovr_Message_GetProductArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrPurchaseHandle)                           ovr_Message_GetPurchase(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrPurchaseArrayHandle)                      ovr_Message_GetPurchaseArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrRejoinDialogResultHandle)                 ovr_Message_GetRejoinDialogResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrRequest)                                  ovr_Message_GetRequestID(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrSdkAccountArrayHandle)                    ovr_Message_GetSdkAccountArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrSendInvitesResultHandle)                  ovr_Message_GetSendInvitesResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrShareMediaResultHandle)                   ovr_Message_GetShareMediaResult(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(const char *)                                ovr_Message_GetString(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrSystemVoipStateHandle)                    ovr_Message_GetSystemVoipState(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrMessageType)                              ovr_Message_GetType(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrUserHandle)                               ovr_Message_GetUser(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrUserAccountAgeCategoryHandle)             ovr_Message_GetUserAccountAgeCategory(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrUserArrayHandle)                          ovr_Message_GetUserArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrUserCapabilityArrayHandle)                ovr_Message_GetUserCapabilityArray(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrUserDataStoreUpdateResponseHandle)        ovr_Message_GetUserDataStoreUpdateResponse(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrUserProofHandle)                          ovr_Message_GetUserProof(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(ovrUserReportIDHandle)                       ovr_Message_GetUserReportID(const ovrMessageHandle obj);
OVRP_PUBLIC_FUNCTION(bool)                                        ovr_Message_IsError(const ovrMessageHandle obj);

#endif
