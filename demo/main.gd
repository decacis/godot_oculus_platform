extends Node3D

var initialized : bool = false


func _on_xr_started():
	if not initialized:
		initialized = true
		GDOP.initialize(false)
		
		# REPLACE APP ID!
		GDOculusPlatform.initialize_android("6324217457624418")
		var launch_details : Dictionary = GDOculusPlatform.application_get_launch_details()
		print("Launch details: ", launch_details)
