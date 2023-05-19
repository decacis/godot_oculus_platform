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
	.then(func(friends : Array):
		print("[user_get_logged_in_user_friends] RESPONSE: ", friends)
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
