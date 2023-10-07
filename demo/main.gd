extends Node3D

var initialized : bool = false


func _on_xr_started():
	if not initialized:

		# REPLACE APP ID!
		initialized = GDOculusPlatform.initialize_android("6324217457624418", { "disable_p2p_networking": true })
		
		if initialized:
			var launch_details : Dictionary = GDOculusPlatform.application_get_launch_details()
			print("Launch details: ", launch_details)
		else:
			print("Unable to initialize Oculus Platform!")
