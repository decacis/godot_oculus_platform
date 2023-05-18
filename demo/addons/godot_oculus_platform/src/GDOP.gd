extends Node

var initialized : bool = false
var quiet : bool = true

var asset_file_callable : Array = []


func _ready() -> void:
	set_process(false)


func initialize(mode_quiet : bool = true) -> void:
	if initialized:
		return
	
	initialized = true
	quiet = mode_quiet
	set_process(true)
	GDOculusPlatform.unhandled_message.connect(_handle_unhandled_message)
	GDOculusPlatform.assetfile_download_finished.connect(_process_download_update)


func _handle_unhandled_message(message : Dictionary) -> void:
	if not quiet:
		print(message)


func call_on_finished_downloading(asset_id : String, func_to_call : Callable):
	asset_file_callable.push_back({
		"id": asset_id,
		"func_to_call": func_to_call
	})

func _process_download_update(asset_file_id : String) -> void:
	for asset_file_info in asset_file_callable:
		
		if asset_file_info.id == asset_file_id:
			asset_file_info.func_to_call.call(asset_file_id)
			asset_file_callable.erase(asset_file_info)
			break


func _process(_delta : float) -> void:
	GDOculusPlatform.pump_messages()
