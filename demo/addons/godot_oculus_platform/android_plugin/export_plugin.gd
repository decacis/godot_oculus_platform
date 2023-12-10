@tool
extends EditorPlugin

# A class member to hold the editor export plugin during its lifecycle.
var export_plugin : AndroidExportPlugin

func _enter_tree():
	# Initialization of the plugin goes here.
	export_plugin = AndroidExportPlugin.new()
	add_export_plugin(export_plugin)


func _exit_tree():
	# Clean-up of the plugin goes here.
	remove_export_plugin(export_plugin)
	export_plugin = null


class AndroidExportPlugin extends EditorExportPlugin:
	# Plugin's name.
	var _plugin_name = "Godot Oculus Platform"

	# Specifies which platform is supported by the plugin.
	func _supports_platform(platform):
		if platform is EditorExportPlatformAndroid:
			return true
		return false

	# Return the paths of the plugin's AAR binaries relative to the 'addons' directory.
	func _get_android_libraries(platform, debug):
		if debug:
			return PackedStringArray(["godot_oculus_platform/android_plugin/godotoculusplatform-android-plugin-debug.aar"])
		else:
			return PackedStringArray(["godot_oculus_platform/android_plugin/godotoculusplatform-android-plugin-release.aar"])

	# Return the plugin's name.
	func _get_name():
		return _plugin_name