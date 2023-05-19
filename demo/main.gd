extends Node3D


func _on_xr_started():
	GDOP.initialize(false)
	
	# REPLACE APP ID!
	GDOculusPlatform.initialize_android("6324217457624418")
