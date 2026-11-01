EventScript_UseSurf::
	goto_if_questlog EventScript_UseSurfEnd
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_UseSurfEnd
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	@ QoL field moves (constants/qol_field_moves.h): no yes/no prompt, optionally no text either
.if QOL_FIELD_MOVES == FALSE
	msgbox Text_WantToSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_UseSurfRelease
.endif
.if QOL_FIELD_MOVES == FALSE || QOL_FIELD_MOVES_NO_MESSAGING == FALSE
	msgbox Text_UsedSurf
.endif
	dofieldeffect FLDEFF_USE_SURF
EventScript_UseSurfRelease:
	releaseall
EventScript_UseSurfEnd:
	end

EventScript_CurrentTooFast::
	lockall
	msgbox Text_CurrentTooFast
	releaseall
	end
