extends Node

var initialized : bool = false
var quiet : bool = true


func _ready() -> void:
	set_process(false)


func initialize(mode_quiet : bool = true) -> void:
	if initialized:
		return
	
	set_process_mode(Node.PROCESS_MODE_ALWAYS)
	initialized = true
	quiet = mode_quiet
	set_process(true)
	GDOculusPlatform.unhandled_message.connect(_handle_unhandled_message)


func _handle_unhandled_message(message : Dictionary) -> void:
	if not quiet:
		print(message)


func _process(_delta : float) -> void:
	GDOculusPlatform.pump_messages()
