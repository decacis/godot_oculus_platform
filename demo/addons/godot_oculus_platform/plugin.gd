@tool
extends EditorPlugin


func _enter_tree():
	if !Engine.has_singleton("GDOP"):
		add_autoload_singleton("GDOP", "res://addons/godot_oculus_platform/src/GDOP.gd")


func _exit_tree():
	# Clean-up of the plugin goes here.
	pass
