EventScript_UseSurf::
	goto_if_questlog EventScript_UseSurfEnd
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_UseSurfEnd
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	QolAutoUseMode VAR_0x8008
	goto_if_ne VAR_0x8008, QOL_AUTO_OFF, EventScript_UseSurfAuto
	msgbox Text_WantToSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_UseSurfRelease
	msgbox Text_UsedSurf
	dofieldeffect FLDEFF_USE_SURF
	goto EventScript_UseSurfRelease

EventScript_UseSurfAuto:
	call_if_eq VAR_0x8008, QOL_AUTO_MSG, EventScript_QolUsedSurf
	dofieldeffect FLDEFF_USE_SURF
EventScript_UseSurfRelease:
	releaseall
EventScript_UseSurfEnd:
	end

EventScript_QolUsedSurf:
	msgbox Text_UsedSurf
	return

EventScript_CurrentTooFast::
	lockall
	msgbox Text_CurrentTooFast
	releaseall
	end
