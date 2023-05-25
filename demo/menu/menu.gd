extends CanvasLayer


@export_group("User")
@export var get_user_val : String = ""
@export var get_org_scoped_id_val : String = ""
@export var launch_block_flow_val : String = ""
@export var launch_unblock_flow_val : String = ""
@export var launch_friend_req_flow_val : String = ""

@export_group("Achievements")
@export var achievements_add_count : Dictionary = {}
@export var achievements_add_fields : Dictionary = {}
@export var achievements_unlock : String = ""
@export var achievements_get_definitions_by_name : Array[String]
@export var achievements_get_progress_by_name : Array[String]

@export_group("IAP")
@export var IAP_get_products_by_sku : Array[String]
@export var IAP_consume_purchase : String
@export var IAP_launch_checkout_flow : String

@export_group("Asset Files")
@export var assetfile_status_by_id : String = ""
@export var assetfile_status_by_name : String = ""
@export var assetfile_download_by_id : String = ""
@export var assetfile_download_by_name : String = ""
@export var assetfile_download_cancel_by_id : String = ""
@export var assetfile_download_cancel_by_name : String = ""
@export var assetfile_delete_by_id : String = ""
@export var assetfile_delete_by_name : String = ""

@export_group("Leaderboard")
@export var leaderboard_get : String = ""
@export var leaderboard_get_entries : Dictionary = {}
@export var leaderboard_get_entries_after_rank : Dictionary = {}
@export var leaderboard_get_entries_by_ids : Dictionary = {}
@export var leaderboard_write_entry : Dictionary = {}
@export var leaderboard_write_entry_with_supplementary_metric : Dictionary = {}

@export_group("Challenges")
@export var challenges_get : String = ""
@export var challenges_get_list : Dictionary = {}
@export var challenges_get_entries : Dictionary = {}
@export var challenges_get_entries_after_rank : Dictionary = {}
@export var challenges_get_entries_by_ids : Dictionary = {}
@export var challenges_join : String = ""
@export var challenges_leave : String = ""
@export var challenges_decline_invite : String = ""


func _ready() -> void:
	if !get_user_val.is_empty():
		$PanelContainer/TabContainer/User/VBoxContainer/InputFuncs/HFlowContainer/GetUser.visible = true
	if !get_org_scoped_id_val.is_empty():
		$PanelContainer/TabContainer/User/VBoxContainer/InputFuncs/HFlowContainer/GetOrgScopedID.visible = true
	if !launch_block_flow_val.is_empty():
		$PanelContainer/TabContainer/User/VBoxContainer/InputFuncs/HFlowContainer/LaunchBlockFlow.visible = true
	if !launch_unblock_flow_val.is_empty():
		$PanelContainer/TabContainer/User/VBoxContainer/InputFuncs/HFlowContainer/LaunchUnblockFlow.visible = true
	if !launch_friend_req_flow_val.is_empty():
		$PanelContainer/TabContainer/User/VBoxContainer/InputFuncs/HFlowContainer/LaunchFriendRequestFlow.visible = true
	
	## ACHIEVEMENTS
	if !achievements_add_count.is_empty():
		$PanelContainer/TabContainer/Achievements/VBoxContainer/InputFuncs/HFlowContainer/AchievementsAddCount.visible = true
	if !achievements_add_fields.is_empty():
		$PanelContainer/TabContainer/Achievements/VBoxContainer/InputFuncs/HFlowContainer/AchievementsAddFields.visible = true
	if !achievements_unlock.is_empty():
		$PanelContainer/TabContainer/Achievements/VBoxContainer/InputFuncs/HFlowContainer/AchievementsUnlock.visible = true
	if !achievements_get_definitions_by_name.is_empty():
		$PanelContainer/TabContainer/Achievements/VBoxContainer/InputFuncs/HFlowContainer/AchievementsGetDefinitionsByName.visible = true
	if !achievements_get_progress_by_name.is_empty():
		$PanelContainer/TabContainer/Achievements/VBoxContainer/InputFuncs/HFlowContainer/AchievementsGetProgressByName.visible = true
		
	## IAP
	if !IAP_get_products_by_sku.is_empty():
		$PanelContainer/TabContainer/IAP/VBoxContainer/InputFuncs/HFlowContainer/IAPGetProductsBySKU.visible = true
	if !IAP_consume_purchase.is_empty():
		$PanelContainer/TabContainer/IAP/VBoxContainer/InputFuncs/HFlowContainer/IAPConsumePurchase.visible = true
	if !IAP_launch_checkout_flow.is_empty():
		$PanelContainer/TabContainer/IAP/VBoxContainer/InputFuncs/HFlowContainer/IAPLaunchCheckoutFlow.visible = true
	
	## ASSET FILES
	GDOculusPlatform.assetfile_download_update.connect(_on_asset_file_update)
	GDOculusPlatform.assetfile_download_finished.connect(_on_asset_file_downloaded)
	
	if !assetfile_status_by_id.is_empty():
		$PanelContainer/TabContainer/AssetFiles/VBoxContainer/InputFuncs/HFlowContainer/AssetfileStatusByID.visible = true
	if !assetfile_status_by_name.is_empty():
		$PanelContainer/TabContainer/AssetFiles/VBoxContainer/InputFuncs/HFlowContainer/AssetfileStatusByName.visible = true
	if !assetfile_download_by_id.is_empty():
		$PanelContainer/TabContainer/AssetFiles/VBoxContainer/InputFuncs/HFlowContainer/AssetfileDownloadByID.visible = true
	if !assetfile_download_by_name.is_empty():
		$PanelContainer/TabContainer/AssetFiles/VBoxContainer/InputFuncs/HFlowContainer/AssetfileDownloadByName.visible = true
	if !assetfile_download_cancel_by_id.is_empty():
		$PanelContainer/TabContainer/AssetFiles/VBoxContainer/InputFuncs/HFlowContainer/AssetfileDownloadCancelByID.visible = true
	if !assetfile_download_cancel_by_name.is_empty():
		$PanelContainer/TabContainer/AssetFiles/VBoxContainer/InputFuncs/HFlowContainer/AssetfileDownloadCancelByName.visible = true
	if !assetfile_delete_by_id.is_empty():
		$PanelContainer/TabContainer/AssetFiles/VBoxContainer/InputFuncs/HFlowContainer/AssetfileDeleteByID.visible = true
	if !assetfile_delete_by_name.is_empty():
		$PanelContainer/TabContainer/AssetFiles/VBoxContainer/InputFuncs/HFlowContainer/AssetfileDeleteByName.visible = true
	
	## LEADERBOARD
	if !leaderboard_get.is_empty():
		$PanelContainer/TabContainer/Leaderboard/VBoxContainer/InputFuncs/HFlowContainer/LeaderboardGet.visible = true
	if !leaderboard_get_entries.is_empty():
		$PanelContainer/TabContainer/Leaderboard/VBoxContainer/InputFuncs/HFlowContainer/LeaderboardGetEntries.visible = true
	if !leaderboard_get_entries_after_rank.is_empty():
		$PanelContainer/TabContainer/Leaderboard/VBoxContainer/InputFuncs/HFlowContainer/LeaderboardGetEntriesAfterRank.visible = true
	if !leaderboard_get_entries_by_ids.is_empty():
		$PanelContainer/TabContainer/Leaderboard/VBoxContainer/InputFuncs/HFlowContainer/LeaderboardGetEntriesByIDs.visible = true
	if !leaderboard_write_entry.is_empty():
		$PanelContainer/TabContainer/Leaderboard/VBoxContainer/InputFuncs/HFlowContainer/LeaderboardWriteEntry.visible = true
	if !leaderboard_write_entry_with_supplementary_metric.is_empty():
		$PanelContainer/TabContainer/Leaderboard/VBoxContainer/InputFuncs/HFlowContainer/LeaderboardWriteEntryWithSupplementaryMetric.visible = true
		
	## CHALLENGES
	if !challenges_get.is_empty():
		$PanelContainer/TabContainer/Challenges/VBoxContainer/InputFuncs/HFlowContainer/ChallengesGet.visible = true
	if !challenges_get_list.is_empty():
		$PanelContainer/TabContainer/Challenges/VBoxContainer/InputFuncs/HFlowContainer/ChallengesGetList.visible = true
	if !challenges_get_entries.is_empty():
		$PanelContainer/TabContainer/Challenges/VBoxContainer/InputFuncs/HFlowContainer/ChallengesGetEntries.visible = true
	if !challenges_get_entries_after_rank.is_empty():
		$PanelContainer/TabContainer/Challenges/VBoxContainer/InputFuncs/HFlowContainer/ChallengesGetEntriesAfterRank.visible = true
	if !challenges_get_entries_by_ids.is_empty():
		$PanelContainer/TabContainer/Challenges/VBoxContainer/InputFuncs/HFlowContainer/ChallengesGetEntriesByIds.visible = true
	if !challenges_join.is_empty():
		$PanelContainer/TabContainer/Challenges/VBoxContainer/InputFuncs/HFlowContainer/ChallengesJoin.visible = true
	if !challenges_leave.is_empty():
		$PanelContainer/TabContainer/Challenges/VBoxContainer/InputFuncs/HFlowContainer/ChallengesLeave.visible = true
	if !challenges_decline_invite.is_empty():
		$PanelContainer/TabContainer/Challenges/VBoxContainer/InputFuncs/HFlowContainer/ChallengesDeclineInvite.visible = true


## USER - NO INPUT FUNCS
func _on_get_logged_in_user_id_pressed():
	print("-------------------------------------")
	print("user_get_logged_in_user_id CALLED")
	var user_id : String = GDOculusPlatform.user_get_logged_in_user_id()
	print("[get_logged_in_user_id] RESPONSE: ", user_id)

func _on_get_logged_in_user_locale_pressed():
	print("-------------------------------------")
	print("user_get_logged_in_user_locale CALLED")
	var user_locale : String = GDOculusPlatform.user_get_logged_in_user_locale()
	print("[user_get_logged_in_user_locale] RESPONSE: ", user_locale)

func _on_get_is_viewer_entitled_pressed():
	print("-------------------------------------")
	print("user_get_is_viewer_entitled CALLED")
	GDOculusPlatform.user_get_is_viewer_entitled()\
	.then(func(viewer_entitled_resp):
		print("[get_is_viewer_entitled] RESPONSE: ", viewer_entitled_resp)
	)\
	.error(func(viewer_entitled_err):
		push_error("[get_is_viewer_entitled] ERROR: ", viewer_entitled_err)
	)

func _on_get_logged_in_user_pressed():
	print("-------------------------------------")
	print("user_get_logged_in_user CALLED")
	GDOculusPlatform.user_get_logged_in_user()\
	.then(func(get_user_resp : Dictionary):
		print("[user_get_logged_in_user] RESPONSE: ", get_user_resp)
	)\
	.error(func(get_user_err):
		push_error("[user_get_logged_in_user] ERROR: ", get_user_err)
	)


func _on_get_user_proof_pressed():
	print("-------------------------------------")
	print("user_get_user_proof CALLED")
	GDOculusPlatform.user_get_user_proof()\
	.then(func(user_proof_resp : String):
		print("[user_get_user_proof] RESPONSE: ", user_proof_resp)
	)\
	.error(func(user_proof_err):
		push_error("[user_get_user_proof] ERROR: ", user_proof_err)
	)

func _on_get_user_access_token_pressed():
	print("-------------------------------------")
	print("user_get_user_access_token CALLED")
	GDOculusPlatform.user_get_user_access_token()\
	.then(func(user_access_token : String):
		print("[user_get_user_access_token] RESPONSE: ", user_access_token)
	)\
	.error(func(user_access_token_err):
		push_error("[user_get_user_access_token] ERROR: ", user_access_token_err)
	)

func _on_get_blocked_users_pressed():
	print("-------------------------------------")
	print("user_get_blocked_users CALLED")
	GDOculusPlatform.user_get_blocked_users()\
	.then(func(blocked_users : Array):
		print("[user_get_blocked_users] RESPONSE: ", blocked_users)
	)\
	.error(func(blocked_users_err):
		push_error("[user_get_blocked_users] ERROR: ", blocked_users_err)
	)

func _on_get_logged_in_user_friends_pressed():
	print("-------------------------------------")
	print("user_get_logged_in_user_friends CALLED")
	GDOculusPlatform.user_get_logged_in_user_friends()\
	.then(func(friends : GDOPUserArray):
		print("[user_get_logged_in_user_friends] RESPONSE: ", await GDOP.users_array_get_all(friends))
		print("Has next page? ", friends.has_next_page)
	)\
	.error(func(friends_err):
		push_error("[user_get_logged_in_user_friends] ERROR: ", friends_err)
	)

func _on_get_sdk_accounts_pressed():
	print("-------------------------------------")
	print("user_get_sdk_accounts CALLED")
	GDOculusPlatform.user_get_sdk_accounts()\
	.then(func(sdk_accounts : Array):
		print("[user_get_sdk_accounts] RESPONSE: ", sdk_accounts)
	)\
	.error(func(sdk_accounts_err):
		push_error("[user_get_sdk_accounts] ERROR: ", sdk_accounts_err)
	)

## USER - INPUT FUNCS
func _on_get_user_pressed():
	print("-------------------------------------")
	print("user_get_user CALLED")
	print("INPUT: ", get_user_val)
	GDOculusPlatform.user_get_user(get_user_val)\
	.then(func(get_user_resp : Dictionary):
		print("[user_get_user] RESPONSE: ", get_user_resp)
	)\
	.error(func(get_user_err):
		push_error("[user_get_user] ERROR: ", get_user_err)
	)

func _on_get_org_scoped_id_pressed():
	print("-------------------------------------")
	print("user_get_org_scoped_id CALLED")
	print("INPUT: ", get_org_scoped_id_val)
	GDOculusPlatform.user_get_org_scoped_id(get_org_scoped_id_val)\
	.then(func(org_scoped_id : String):
		print("[user_get_org_scoped_id] RESPONSE: ", org_scoped_id)
	)\
	.error(func(org_scoped_id_err):
		push_error("[user_get_org_scoped_id] ERROR: ", org_scoped_id_err)
	)

func _on_launch_block_flow_pressed():
	print("-------------------------------------")
	print("user_launch_block_flow CALLED")
	print("INPUT: ", launch_block_flow_val)
	GDOculusPlatform.user_launch_block_flow(launch_block_flow_val)\
	.then(func(block_flow_resp : Dictionary):
		print("[user_launch_block_flow] RESPONSE: ", block_flow_resp)
	)\
	.error(func(block_flow_err):
		push_error("[user_launch_block_flow] ERROR: ", block_flow_err)
	)

func _on_launch_unblock_flow_pressed():
	print("-------------------------------------")
	print("user_launch_unblock_flow CALLED")
	print("INPUT: ", launch_unblock_flow_val)
	GDOculusPlatform.user_launch_unblock_flow(launch_unblock_flow_val)\
	.then(func(unblock_flow_resp : Dictionary):
		print("[user_launch_unblock_flow] RESPONSE: ", unblock_flow_resp)
	)\
	.error(func(unblock_flow_err):
		push_error("[user_launch_unblock_flow] ERROR: ", unblock_flow_err)
	)

func _on_launch_friend_request_flow_pressed():
	print("-------------------------------------")
	print("user_launch_friend_request_flow CALLED")
	print("INPUT: ", launch_friend_req_flow_val)
	GDOculusPlatform.user_launch_friend_request_flow(launch_friend_req_flow_val)\
	.then(func(friend_req_flow_resp : Dictionary):
		print("[user_launch_friend_request_flow] RESPONSE: ", friend_req_flow_resp)
	)\
	.error(func(friend_req_flow_err):
		push_error("[user_launch_friend_request_flow] ERROR: ", friend_req_flow_err)
	)


## ACHIEVEMENTS - NO INPUT FUNCS
func _on_achievements_get_all_definitions_pressed():
	print("-------------------------------------")
	print("achievements_get_all_definitions CALLED")
	GDOculusPlatform.achievements_get_all_definitions()\
	.then(func(achievements : Array):
		print("[achievements_get_all_definitions] RESPONSE: ", achievements)
	)\
	.error(func(achievements_err):
		push_error("[achievements_get_all_definitions] ERROR: ", achievements_err)
	)

func _on_achievements_get_all_progress_pressed():
	print("-------------------------------------")
	print("achievements_get_all_progress CALLED")
	GDOculusPlatform.achievements_get_all_progress()\
	.then(func(progress : Array):
		print("[achievements_get_all_progress] RESPONSE: ", progress)
	)\
	.error(func(progress_err):
		push_error("[achievements_get_all_progress] ERROR: ", progress_err)
	)

## ACHIEVEMENTS - INPUT FUNCS
func _on_achievements_add_count_pressed():
	print("-------------------------------------")
	print("achievements_add_count CALLED")
	print("INPUT: ", achievements_add_count)
	GDOculusPlatform.achievements_add_count(achievements_add_count.achievement_name, achievements_add_count.count)\
	.then(func(add_count_resp : Dictionary):
		print("[achievements_add_count] RESPONSE: ", add_count_resp)
	)\
	.error(func(add_count_err):
		push_error("[achievements_add_count] ERROR: ", add_count_err)
	)

func _on_achievements_add_fields_pressed():
	print("-------------------------------------")
	print("achievements_add_fields CALLED")
	print("INPUT: ", achievements_add_fields)
	GDOculusPlatform.achievements_add_fields(achievements_add_fields.achievement_name, achievements_add_fields.fields)\
	.then(func(add_fields_resp : Dictionary):
		print("[achievements_add_fields] RESPONSE: ", add_fields_resp)
	)\
	.error(func(add_fields_err):
		push_error("[achievements_add_fields] ERROR: ", add_fields_err)
	)

func _on_achievements_unlock_pressed():
	print("-------------------------------------")
	print("achievements_unlock CALLED")
	print("INPUT: ", achievements_unlock)
	GDOculusPlatform.achievements_unlock(achievements_unlock)\
	.then(func(unlock_resp : Dictionary):
		print("[achievements_unlock] RESPONSE: ", unlock_resp)
	)\
	.error(func(unlock_err):
		push_error("[achievements_unlock] ERROR: ", unlock_err)
	)

func _on_achievements_get_definitions_by_name_pressed():
	print("-------------------------------------")
	print("achievements_get_definitions_by_name CALLED")
	print("INPUT: ", achievements_get_definitions_by_name)
	GDOculusPlatform.achievements_get_definitions_by_name(achievements_get_definitions_by_name)\
	.then(func(defs_by_name_resp : Array):
		print("[achievements_get_definitions_by_name] RESPONSE: ", defs_by_name_resp)
	)\
	.error(func(defs_by_name_err):
		push_error("[achievements_get_definitions_by_name] ERROR: ", defs_by_name_err)
	)

func _on_achievements_get_progress_by_name_pressed():
	print("-------------------------------------")
	print("achievements_get_progress_by_name CALLED")
	print("INPUT: ", achievements_get_progress_by_name)
	GDOculusPlatform.achievements_get_progress_by_name(achievements_get_progress_by_name)\
	.then(func(prog_by_name_resp : Array):
		print("[achievements_get_progress_by_name] RESPONSE: ", prog_by_name_resp)
	)\
	.error(func(prog_by_name_err):
		push_error("[achievements_get_progress_by_name] ERROR: ", prog_by_name_err)
	)


## IAP - NO INPUT FUNCS
func _on_iap_get_viewer_purchases_pressed():
	print("-------------------------------------")
	print("iap_get_viewer_purchases CALLED")
	GDOculusPlatform.iap_get_viewer_purchases()\
	.then(func(viewer_purchases : Array):
		print("[iap_get_viewer_purchases] RESPONSE: ", viewer_purchases)
	)\
	.error(func(viewer_purchases_err):
		push_error("[iap_get_viewer_purchases] ERROR: ", viewer_purchases_err)
	)

## IAP - INPUT FUNCS
func _on_iap_get_products_by_sku_pressed():
	print("-------------------------------------")
	print("iap_get_products_by_sku CALLED")
	print("INPUT: ", IAP_get_products_by_sku)
	GDOculusPlatform.iap_get_products_by_sku(IAP_get_products_by_sku)\
	.then(func(products : Array):
		print("[iap_get_products_by_sku] RESPONSE: ", products)
	)\
	.error(func(products_err):
		push_error("[iap_get_products_by_sku] ERROR: ", products_err)
	)


func _on_iap_consume_purchase_pressed():
	print("-------------------------------------")
	print("iap_consume_purchase CALLED")
	print("INPUT: ", IAP_consume_purchase)
	GDOculusPlatform.iap_consume_purchase(IAP_consume_purchase)\
	.then(func(consume_resp : bool):
		print("[iap_consume_purchase] RESPONSE: ", consume_resp)
	)\
	.error(func(consume_err):
		push_error("[iap_consume_purchase] ERROR: ", consume_err)
	)


func _on_iap_launch_checkout_flow_pressed():
	print("-------------------------------------")
	print("iap_launch_checkout_flow CALLED")
	print("INPUT: ", IAP_launch_checkout_flow)
	GDOculusPlatform.iap_launch_checkout_flow(IAP_launch_checkout_flow)\
	.then(func(checkout_resp : Dictionary):
		print("[iap_launch_checkout_flow] RESPONSE: ", checkout_resp)
	)\
	.error(func(checkout_err):
		
		if typeof(checkout_err) == TYPE_DICTIONARY\
		and checkout_err.has("category")\
		and checkout_err.category == "user_canceled":
			print("[iap_launch_checkout_flow] RESPONSE: ", checkout_err)
		else:
			push_error("[iap_launch_checkout_flow] ERROR: ", checkout_err)
	)


## ASSET FILES
var should_init : bool = true
func _on_asset_file_update(asset_file_update : Dictionary) -> void:
	print("asset_file_update: ", asset_file_update)
	if asset_file_update.total_bytes == 0:
		return
	
	if should_init:
		should_init = false
		_init_download_status(asset_file_update.total_bytes)
	
	var update_txt : String = "{bytes_prog} / {bytes_total}".format({
		bytes_prog = asset_file_update.transferred_bytes,
		bytes_total = asset_file_update.total_bytes,
	})
	$PanelContainer/TabContainer/AssetFiles/VBoxContainer/DownloadStatus/HBoxContainer/VBoxContainer/DownloadProgressValLbl.text = update_txt
	$PanelContainer/TabContainer/AssetFiles/VBoxContainer/DownloadStatus/HBoxContainer/VBoxContainer/ProgressBar.value = asset_file_update.transferred_bytes

func _on_asset_file_downloaded(asset_id : String):
	print("[ASSET FILE DOWNLOAD] Finished!")
	$PanelContainer/TabContainer/AssetFiles/VBoxContainer/DownloadStatus/HBoxContainer/DownloadFinishedLbl.visible = true

func _init_download_status(max_val : int) -> void:
	$PanelContainer/TabContainer/AssetFiles/VBoxContainer/DownloadStatus/HBoxContainer/VBoxContainer/DownloadProgressValLbl.text = "0 / 0"
	$PanelContainer/TabContainer/AssetFiles/VBoxContainer/DownloadStatus/HBoxContainer/VBoxContainer/ProgressBar.value = 0
	$PanelContainer/TabContainer/AssetFiles/VBoxContainer/DownloadStatus/HBoxContainer/VBoxContainer/ProgressBar.max_value = max_val
	$PanelContainer/TabContainer/AssetFiles/VBoxContainer/DownloadStatus/HBoxContainer/DownloadFinishedLbl.visible = false

## ASSET FILES - NO INPUT FUNCS
func _on_assetfile_get_list_pressed():
	print("-------------------------------------")
	print("assetfile_get_list CALLED")
	GDOculusPlatform.assetfile_get_list()\
	.then(func(asset_files : Array):
		print("[assetfile_get_list] RESPONSE: ", asset_files)
	)\
	.error(func(asset_files_err):
		push_error("[assetfile_get_list] ERROR: ", asset_files_err)
	)

## ASSET FILES - INPUT FUNCS
func _on_assetfile_status_by_id_pressed():
	print("-------------------------------------")
	print("assetfile_status_by_id CALLED")
	print("INPUT: ", assetfile_status_by_id)
	GDOculusPlatform.assetfile_status_by_id(assetfile_status_by_id)\
	.then(func(asset_files_s : Dictionary):
		print("[assetfile_status_by_id] RESPONSE: ", asset_files_s)
	)\
	.error(func(asset_files_s_err):
		push_error("[assetfile_status_by_id] ERROR: ", asset_files_s_err)
	)

func _on_assetfile_status_by_name_pressed():
	print("-------------------------------------")
	print("assetfile_status_by_name CALLED")
	print("INPUT: ", assetfile_status_by_name)
	GDOculusPlatform.assetfile_status_by_name(assetfile_status_by_name)\
	.then(func(asset_files_s : Dictionary):
		print("[assetfile_status_by_name] RESPONSE: ", asset_files_s)
	)\
	.error(func(asset_files_s_err):
		push_error("[assetfile_status_by_name] ERROR: ", asset_files_s_err)
	)

func _on_assetfile_download_by_id_pressed():
	print("-------------------------------------")
	print("assetfile_download_by_id CALLED")
	print("INPUT: ", assetfile_download_by_id)
	GDOculusPlatform.assetfile_download_by_id(assetfile_download_by_id)\
	.then(func(asset_files_d : Dictionary):
		should_init = true
		print("[assetfile_download_by_id] RESPONSE: ", asset_files_d)
	)\
	.error(func(asset_files_d_err):
		push_error("[assetfile_download_by_id] ERROR: ", asset_files_d_err)
	)

func _on_assetfile_download_by_name_pressed():
	print("-------------------------------------")
	print("assetfile_download_by_name CALLED")
	print("INPUT: ", assetfile_download_by_name)
	GDOculusPlatform.assetfile_download_by_name(assetfile_download_by_name)\
	.then(func(asset_files_d : Dictionary):
		should_init = true
		print("[assetfile_download_by_name] RESPONSE: ", asset_files_d)
	)\
	.error(func(asset_files_d_err):
		push_error("[assetfile_download_by_name] ERROR: ", asset_files_d_err)
	)

func _on_assetfile_download_cancel_by_id_pressed():
	print("-------------------------------------")
	print("assetfile_download_cancel_by_id CALLED")
	print("INPUT: ", assetfile_download_cancel_by_id)
	GDOculusPlatform.assetfile_download_cancel_by_id(assetfile_download_cancel_by_id)\
	.then(func(asset_files_d_c : Dictionary):
		print("[assetfile_download_cancel_by_id] RESPONSE: ", asset_files_d_c)
	)\
	.error(func(asset_files_d_c_err):
		push_error("[assetfile_download_cancel_by_id] ERROR: ", asset_files_d_c_err)
	)

func _on_assetfile_download_cancel_by_name_pressed():
	print("-------------------------------------")
	print("assetfile_download_cancel_by_name CALLED")
	print("INPUT: ", assetfile_download_cancel_by_name)
	GDOculusPlatform.assetfile_download_cancel_by_name(assetfile_download_cancel_by_name)\
	.then(func(asset_files_d_c : Dictionary):
		print("[assetfile_download_cancel_by_name] RESPONSE: ", asset_files_d_c)
	)\
	.error(func(asset_files_d_c_err):
		push_error("[assetfile_download_cancel_by_name] ERROR: ", asset_files_d_c_err)
	)

func _on_assetfile_delete_by_id_pressed():
	print("-------------------------------------")
	print("assetfile_delete_by_id CALLED")
	print("INPUT: ", assetfile_delete_by_id)
	GDOculusPlatform.assetfile_delete_by_id(assetfile_delete_by_id)\
	.then(func(asset_files_del : Dictionary):
		print("[assetfile_delete_by_id] RESPONSE: ", asset_files_del)
	)\
	.error(func(asset_files_del_err):
		push_error("[assetfile_delete_by_id] ERROR: ", asset_files_del_err)
	)

func _on_assetfile_delete_by_name_pressed():
	print("-------------------------------------")
	print("assetfile_delete_by_name CALLED")
	print("INPUT: ", assetfile_delete_by_name)
	GDOculusPlatform.assetfile_delete_by_name(assetfile_delete_by_name)\
	.then(func(asset_files_del : Dictionary):
		print("[assetfile_delete_by_name] RESPONSE: ", asset_files_del)
	)\
	.error(func(asset_files_del_err):
		push_error("[assetfile_delete_by_name] ERROR: ", asset_files_del_err)
	)


## LEADERBOARD - INPUT FUNCS
func _on_leaderboard_get_pressed():
	print("-------------------------------------")
	print("leaderboard_get CALLED")
	print("INPUT: ", leaderboard_get)
	GDOculusPlatform.leaderboard_get(leaderboard_get)\
	.then(func(leaderboard_info : Dictionary):
		print("[leaderboard_get] RESPONSE: ", leaderboard_info)
	)\
	.error(func(leaderboard_err):
		push_error("[leaderboard_get] ERROR: ", leaderboard_err)
	)

func _on_leaderboard_get_entries_pressed():
	print("-------------------------------------")
	print("leaderboard_get_entries CALLED")
	print("INPUT: ", leaderboard_get_entries)
	GDOculusPlatform.leaderboard_get_entries(leaderboard_get_entries.name,\
	leaderboard_get_entries.limit,\
	leaderboard_get_entries.filter,\
	leaderboard_get_entries.start_at\
	)\
	.then(func(leaderboard_e_resp : GDOPLeaderboardEntries):
		print("[leaderboard_get_entries] RESPONSE: ", await GDOP.leaderboard_entries_get_all(leaderboard_e_resp))
	)\
	.error(func(leaderboard_err):
		push_error("[leaderboard_get_entries] ERROR: ", leaderboard_err)
	)

func _on_leaderboard_get_entries_after_rank_pressed():
	print("-------------------------------------")
	print("leaderboard_get_entries_after_rank CALLED")
	print("INPUT: ", leaderboard_get_entries_after_rank)
	GDOculusPlatform.leaderboard_get_entries_after_rank(leaderboard_get_entries_after_rank.name,\
	leaderboard_get_entries_after_rank.limit,\
	leaderboard_get_entries_after_rank.after_rank\
	)\
	.then(func(leaderboard_e_resp : GDOPLeaderboardEntries):
		print("[leaderboard_get_entries_after_rank] RESPONSE: ", await GDOP.leaderboard_entries_get_all(leaderboard_e_resp))
	)\
	.error(func(leaderboard_err):
		push_error("[leaderboard_get_entries_after_rank] ERROR: ", leaderboard_err)
	)

func _on_leaderboard_get_entries_by_i_ds_pressed():
	print("-------------------------------------")
	print("leaderboard_get_entries_by_ids CALLED")
	print("INPUT: ", leaderboard_get_entries_by_ids)
	GDOculusPlatform.leaderboard_get_entries_by_ids(leaderboard_get_entries_by_ids.name,\
	leaderboard_get_entries_by_ids.limit,\
	leaderboard_get_entries_by_ids.user_ids,\
	leaderboard_get_entries_by_ids.start_at\
	)\
	.then(func(leaderboard_e_resp : GDOPLeaderboardEntries):
		print("[leaderboard_get_entries_by_ids] RESPONSE: ", await GDOP.leaderboard_entries_get_all(leaderboard_e_resp))
	)\
	.error(func(leaderboard_err):
		push_error("[leaderboard_get_entries_by_ids] ERROR: ", leaderboard_err)
	)

func _on_leaderboard_write_entry_pressed():
	print("-------------------------------------")
	print("leaderboard_write_entry CALLED")
	print("INPUT: ", leaderboard_write_entry)
	GDOculusPlatform.leaderboard_write_entry(leaderboard_write_entry.name,\
	leaderboard_write_entry.score,\
	leaderboard_write_entry.force_update,\
	leaderboard_write_entry.extra\
	)\
	.then(func(leaderboard_e_resp : Dictionary):
		print("[leaderboard_write_entry] RESPONSE: ", leaderboard_e_resp)
	)\
	.error(func(leaderboard_err):
		push_error("[leaderboard_write_entry] ERROR: ", leaderboard_err)
	)

func _on_leaderboard_write_entry_with_supplementary_metric_pressed():
	print("-------------------------------------")
	print("leaderboard_write_entry with supplementary metric CALLED")
	print("INPUT: ", leaderboard_write_entry_with_supplementary_metric)
	GDOculusPlatform.leaderboard_write_entry(leaderboard_write_entry_with_supplementary_metric.name,\
	leaderboard_write_entry_with_supplementary_metric.score,\
	leaderboard_write_entry_with_supplementary_metric.force_update,\
	leaderboard_write_entry_with_supplementary_metric.extra\
	)\
	.then(func(leaderboard_e_resp : Dictionary):
		print("[leaderboard_write_entry with supplementary metric] RESPONSE: ", leaderboard_e_resp)
	)\
	.error(func(leaderboard_err):
		push_error("[leaderboard_write_entry with supplementary metric] ERROR: ", leaderboard_err)
	)


## CHALLENGES - INPUT FUNCS
func _on_challenges_get_pressed():
	pass # Replace with function body.

func _on_challenges_get_list_pressed():
	pass # Replace with function body.

func _on_challenges_get_entries_pressed():
	pass # Replace with function body.

func _on_challenges_get_entries_after_rank_pressed():
	pass # Replace with function body.

func _on_challenges_get_entries_by_ids_pressed():
	pass # Replace with function body.

func _on_challenges_join_pressed():
	pass # Replace with function body.

func _on_challenges_leave_pressed():
	pass # Replace with function body.

func _on_challenges_decline_invite_pressed():
	pass # Replace with function body.
