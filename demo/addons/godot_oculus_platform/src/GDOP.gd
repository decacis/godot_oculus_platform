extends Node

signal users_array_get_all_finished(event_id : int)
signal leaderboard_entries_get_all_prev_finished(event_id : int)
signal leaderboard_entries_get_all_next_finished(event_id : int)
signal challenge_array_get_all_prev_finished(event_id : int)
signal challenge_array_get_all_next_finished(event_id : int)
signal challenge_entries_get_all_prev_finished(event_id : int)
signal challenge_entries_get_all_next_finished(event_id : int)

var initialized : bool = false
var quiet : bool = true

var helper_events_ids : PackedInt32Array = []


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


## GDOPUserArray
func users_array_get_all(user_array : GDOPUserArray) -> Array:
	if user_array.get_has_next_page():
		var users : Array = user_array.users.duplicate(true)
		
		var event_id : int = randi()
		while helper_events_ids.has(event_id):
			event_id = randi()
		_users_array_get_all_helper(user_array, users, event_id)
		
		var returned_event_id = await users_array_get_all_finished
		while returned_event_id != event_id:
			returned_event_id = await users_array_get_all_finished
		
		helper_events_ids.remove_at(helper_events_ids.find(event_id))
		
		return users
		
	else:
		return user_array.users

func _users_array_get_all_helper(user_array : GDOPUserArray, users : Array, event_id : int) -> void:
	GDOculusPlatform.user_array_get_next_page(user_array)\
	.then(func(next_array : GDOPUserArray):
		users.append_array(next_array.users)
		
		if not next_array.get_has_next_page():
			emit_signal("users_array_get_all_finished", event_id)
			
		else:
			_users_array_get_all_helper(next_array, users, event_id)
	)\
	.error(func(next_array_err):
		push_error(next_array_err)
		# Don't stop the game
		emit_signal("users_array_get_all_finished", event_id)
	)


## GDOPLeaderboardEntries
func leaderboard_entries_get_all(leaderboard_entries : GDOPLeaderboardEntries) -> Array:
	if leaderboard_entries.get_has_prev_page() or leaderboard_entries.get_has_next_page():
		var entries : Array = []
		
		var event_id : int = randi()
		while helper_events_ids.has(event_id):
			event_id = randi()
		_leaderboard_entries_get_all_prev_helper(leaderboard_entries, entries, event_id)
		
		var returned_event_id = await leaderboard_entries_get_all_prev_finished
		while returned_event_id != event_id:
			returned_event_id = await leaderboard_entries_get_all_prev_finished
		
		helper_events_ids.remove_at(helper_events_ids.find(event_id))
		
		entries.append_array(leaderboard_entries.entries)
		var event_id_2 : int = randi()
		while helper_events_ids.has(event_id_2):
			event_id_2 = randi()
		_leaderboard_entries_get_all_next_helper(leaderboard_entries, entries, event_id_2)
		
		var returned_event_id_2 = await leaderboard_entries_get_all_next_finished
		while returned_event_id_2 != event_id_2:
			returned_event_id_2 = await leaderboard_entries_get_all_next_finished
		
		helper_events_ids.remove_at(helper_events_ids.find(event_id_2))
		
		return entries
		
	else:
		return leaderboard_entries.entries

func _leaderboard_entries_get_all_prev_helper(leaderboard_entries : GDOPLeaderboardEntries, entries : Array, event_id : int) -> void:
	
	if leaderboard_entries.get_has_prev_page():
		GDOculusPlatform.leaderboard_entries_get_prev_page(leaderboard_entries)\
		.then(func(prev_array : GDOPLeaderboardEntries):
			var temp_array : Array = []
			temp_array.append_array(prev_array.entries)
			temp_array.append_array(entries)
			
			entries = temp_array
			
			if not prev_array.get_has_prev_page():
				emit_signal("leaderboard_entries_get_all_prev_finished", event_id)
				
			else:
				_leaderboard_entries_get_all_prev_helper(prev_array, entries, event_id)
		)\
		.error(func(next_array_err):
			push_error(next_array_err)
			# Don't stop the game
			emit_signal("leaderboard_entries_get_all_prev_finished", event_id)
		)
	
	else:
		emit_signal("leaderboard_entries_get_all_prev_finished", event_id)

func _leaderboard_entries_get_all_next_helper(leaderboard_entries : GDOPLeaderboardEntries, entries : Array, event_id : int) -> void:
	
	if leaderboard_entries.get_has_next_page():
		GDOculusPlatform.leaderboard_entries_get_next_page(leaderboard_entries)\
		.then(func(next_array : GDOPLeaderboardEntries):
			entries.append(next_array.entries)
			
			if not next_array.get_has_next_page():
				emit_signal("leaderboard_entries_get_all_next_finished", event_id)
				
			else:
				_leaderboard_entries_get_all_next_helper(next_array, entries, event_id)
		)\
		.error(func(next_array_err):
			push_error(next_array_err)
			# Don't stop the game
			emit_signal("leaderboard_entries_get_all_next_finished", event_id)
		)
	
	else:
		emit_signal("leaderboard_entries_get_all_next_finished", event_id)


## GDOPChallengeArray
func challenge_array_get_all(challenge_array : GDOPChallengeArray) -> Array:
	if challenge_array.get_has_prev_page() or challenge_array.get_has_next_page():
		var challenges : Array = []
		
		var event_id : int = randi()
		while helper_events_ids.has(event_id):
			event_id = randi()
		_challenge_array_get_all_prev_helper(challenge_array, challenges, event_id)
		
		var returned_event_id = await challenge_array_get_all_prev_finished
		while returned_event_id != event_id:
			returned_event_id = await challenge_array_get_all_prev_finished
		
		helper_events_ids.remove_at(helper_events_ids.find(event_id))
		
		challenges.append_array(challenge_array.challenges)
		var event_id_2 : int = randi()
		while helper_events_ids.has(event_id_2):
			event_id_2 = randi()
		_challenge_array_get_all_next_helper(challenge_array, challenges, event_id_2)
		
		var returned_event_id_2 = await challenge_array_get_all_next_finished
		while returned_event_id_2 != event_id_2:
			returned_event_id_2 = await challenge_array_get_all_next_finished
			
		helper_events_ids.remove_at(helper_events_ids.find(event_id_2))
		
		return challenges
		
	else:
		return challenge_array.challenges

func _challenge_array_get_all_prev_helper(challenge_array : GDOPChallengeArray, challenges : Array, event_id : int) -> void:
	
	if challenge_array.get_has_prev_page():
		GDOculusPlatform.challenge_array_get_prev_page(challenge_array)\
		.then(func(prev_array : GDOPChallengeArray):
			var temp_array : Array = []
			temp_array.append_array(prev_array.challenges)
			temp_array.append_array(challenges)
			
			challenges = temp_array
			
			if not prev_array.get_has_prev_page():
				emit_signal("challenge_array_get_all_prev_finished", event_id)
				
			else:
				_challenge_array_get_all_prev_helper(prev_array, challenges, event_id)
		)\
		.error(func(next_array_err):
			push_error(next_array_err)
			# Don't stop the game
			emit_signal("challenge_array_get_all_prev_finished", event_id)
		)
	
	else:
		emit_signal("challenge_array_get_all_prev_finished", event_id)

func _challenge_array_get_all_next_helper(challenge_array : GDOPChallengeArray, challenges : Array, event_id : int) -> void:
	
	if challenge_array.get_has_next_page():
		GDOculusPlatform.challenge_array_get_next_page(challenge_array)\
		.then(func(next_array : GDOPChallengeArray):
			challenges.append(next_array.challenges)
			
			if not next_array.get_has_next_page():
				emit_signal("challenge_array_get_all_next_finished", event_id)
				
			else:
				_challenge_array_get_all_next_helper(next_array, challenges, event_id)
		)\
		.error(func(next_array_err):
			push_error(next_array_err)
			# Don't stop the game
			emit_signal("challenge_array_get_all_next_finished", event_id)
		)
	
	else:
		emit_signal("challenge_array_get_all_next_finished", event_id)


## GDOPChallengeEntries
func challenge_entries_get_all(challenge_entries : GDOPChallengeEntries) -> Array:
	if challenge_entries.get_has_prev_page() or challenge_entries.get_has_next_page():
		var entries : Array = []
		
		var event_id : int = randi()
		while helper_events_ids.has(event_id):
			event_id = randi()
		_challenge_entries_get_all_prev_helper(challenge_entries, entries, event_id)
		
		var returned_event_id = await challenge_entries_get_all_prev_finished
		while returned_event_id != event_id:
			returned_event_id = await challenge_entries_get_all_prev_finished
		
		helper_events_ids.remove_at(helper_events_ids.find(event_id))
		
		entries.append_array(challenge_entries.entries)
		var event_id_2 : int = randi()
		while helper_events_ids.has(event_id_2):
			event_id_2 = randi()
		_challenge_entries_get_all_next_helper(challenge_entries, entries, event_id_2)
		
		var returned_event_id_2 = await challenge_entries_get_all_next_finished
		while returned_event_id_2 != event_id_2:
			returned_event_id_2 = await challenge_entries_get_all_next_finished
			
		helper_events_ids.remove_at(helper_events_ids.find(event_id_2))
		
		return entries
		
	else:
		return challenge_entries.entries

func _challenge_entries_get_all_prev_helper(challenge_entries : GDOPChallengeEntries, entries : Array, event_id : int) -> void:
	
	if challenge_entries.get_has_prev_page():
		GDOculusPlatform.challenge_entries_get_prev_page(challenge_entries)\
		.then(func(prev_array : GDOPChallengeEntries):
			var temp_array : Array = []
			temp_array.append_array(prev_array.entries)
			temp_array.append_array(entries)
			
			entries = temp_array
			
			if not prev_array.get_has_prev_page():
				emit_signal("challenge_entries_get_all_prev_finished", event_id)
				
			else:
				_challenge_entries_get_all_prev_helper(prev_array, entries, event_id)
		)\
		.error(func(next_array_err):
			push_error(next_array_err)
			# Don't stop the game
			emit_signal("challenge_entries_get_all_prev_finished", event_id)
		)
	
	else:
		emit_signal("challenge_entries_get_all_prev_finished", event_id)

func _challenge_entries_get_all_next_helper(challenge_entries : GDOPChallengeEntries, entries : Array, event_id : int) -> void:
	
	if challenge_entries.get_has_next_page():
		GDOculusPlatform.challenge_entries_get_next_page(challenge_entries)\
		.then(func(next_array : GDOPChallengeEntries):
			entries.append(next_array.entries)
			
			if not next_array.get_has_next_page():
				emit_signal("challenge_entries_get_all_next_finished", event_id)
				
			else:
				_challenge_entries_get_all_next_helper(next_array, entries, event_id)
		)\
		.error(func(next_array_err):
			push_error(next_array_err)
			# Don't stop the game
			emit_signal("challenge_entries_get_all_next_finished", event_id)
		)
	
	else:
		emit_signal("challenge_entries_get_all_next_finished", event_id)
