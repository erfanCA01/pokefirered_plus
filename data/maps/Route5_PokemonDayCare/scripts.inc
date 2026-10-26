@ Handled by data/scripts/day_care.inc

Route5_PokemonDayCare_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route5_PokemonDayCare_OnTransition
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, Route5_PokemonDayCare_OnReturnToField
	.byte 0

@ followers-expanded-id: the mon being raised walks around inside the Day Care (shown by an object
@ whose graphics come from VAR_OBJ_GFX_ID_C and whose shininess comes from VAR_TEMP_0)
Route5_PokemonDayCare_OnTransition:
	setflag FLAG_TEMP_1
	getroute5daycaregfx VAR_OBJ_GFX_ID_C, VAR_TEMP_0
	goto_if_eq VAR_RESULT, 1, Route5_PokemonDayCare_EventScript_ShowDaycareMon
	end

Route5_PokemonDayCare_EventScript_ShowDaycareMon:
	clearflag FLAG_TEMP_1
	end

@ The Day Care mon object is never stored in the save (see SaveObjectEvents), so put it back after
@ Continue. addobject does nothing if the mon is already there (ordinary returns from a menu or battle).
Route5_PokemonDayCare_OnReturnToField:
	getroute5daycaregfx VAR_OBJ_GFX_ID_C, VAR_TEMP_0
	goto_if_ne VAR_RESULT, 1, Route5_PokemonDayCare_EventScript_ReturnToFieldDone
	clearflag FLAG_TEMP_1
	addobject LOCALID_ROUTE5_DAYCARE_MON
Route5_PokemonDayCare_EventScript_ReturnToFieldDone:
	end

@ Called right after a mon is left with / taken back from the Day Care man, so the change shows at once
Route5_PokemonDayCare_EventScript_RefreshDaycareMon::
	removeobject LOCALID_ROUTE5_DAYCARE_MON
	setflag FLAG_TEMP_1
	getroute5daycaregfx VAR_OBJ_GFX_ID_C, VAR_TEMP_0
	goto_if_ne VAR_RESULT, 1, Route5_PokemonDayCare_EventScript_RefreshDone
	clearflag FLAG_TEMP_1
	addobject LOCALID_ROUTE5_DAYCARE_MON
Route5_PokemonDayCare_EventScript_RefreshDone:
	return
