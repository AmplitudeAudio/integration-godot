extends Node

var suspend_on_focus_loss: bool = false;

func _init() -> void:
	suspend_on_focus_loss = ProjectSettings.get_setting("amplitude_audio/user_settings/suspend_on_focus_loss", false)
	process_mode = Node.PROCESS_MODE_ALWAYS
	Amplitude.init()
	
func _process(delta: float) -> void:
	if Amplitude.is_initialized():
		Amplitude.advance_frame(delta)
