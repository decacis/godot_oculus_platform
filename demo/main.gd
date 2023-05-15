extends Node3D

var interface: XRInterface

func _ready():
	interface = XRServer.find_interface("OpenXR")
	if interface and interface.is_initialized():
		print("OpenXR initialised successfully")

		# Turn off v-sync!
		DisplayServer.window_set_vsync_mode(DisplayServer.VSYNC_DISABLED)
		Engine.physics_ticks_per_second = 72

		# Change our main viewport to output to the HMD
		get_viewport().use_xr = true
		
		print("About to initialize Oculus Platform asynchronously")
		
		GDOP.initialize(false)
		# REPLACE APP ID!
		GDOculusPlatform.initialize_android_async("6324217457624418")\
		.then(func(_initialization_resp):
			print("Oculus Platform initialized")
			
			GDOculusPlatform.get_is_viewer_entitled()\
			.then(func(_is_viewer_entitled_resp):
				print("User is entitled!")
				
				GDOculusPlatform.get_logged_in_user()\
				.then(func(user_info):
					print("User info: ", user_info)
					
#					GDOculusPlatform.get_user("USER_ID_HERE")\
#					.then(func(get_user_resp):
#						print("Get user fulfilled! ", get_user_resp)
#					)\
#					.error(func(get_user_err):
#						print("Get user error: ", get_user_err)
#					)

#					GDOculusPlatform.get_user_access_token()\
#					.then(func(user_access_token):
#						print("User access token: ", user_access_token)
#					)\
#					.error(func(user_access_token_err):
#						print("User access token error: ", user_access_token_err)
#					)
					
					GDOculusPlatform.get_blocked_users()\
					.then(func(blocked_user_ids):
						print("Blocked user ids: ", blocked_user_ids)
					)\
					.error(func(blocked_users_error):
						print("Blocked users error: ", blocked_users_error)
					)
					
				)\
				.error(func(user_info_err):
					print("User info error: ", user_info_err)
				)
				
			)\
			.error(func(is_viewer_entitled_err):
				print("User not entitled/error! ", is_viewer_entitled_err)
			)
			
		)\
		.error(func(initialization_err):
			print("Oculus Platform initialization error: ", initialization_err)
		)
		
	else:
		print("OpenXR not initialised, please check if your headset is connected")
