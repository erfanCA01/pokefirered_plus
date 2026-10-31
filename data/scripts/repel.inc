EventScript_RepelWoreOff::
	checkitem ITEM_REPEL, 1
	goto_if_eq VAR_RESULT, TRUE, EventScript_AskUseAnotherRepel
	checkitem ITEM_SUPER_REPEL, 1
	goto_if_eq VAR_RESULT, TRUE, EventScript_AskUseAnotherRepel
	checkitem ITEM_MAX_REPEL, 1
	goto_if_eq VAR_RESULT, TRUE, EventScript_AskUseAnotherRepel
	msgbox Text_RepelWoreOff, MSGBOX_SIGN
	end

EventScript_AskUseAnotherRepel::
	lockall
	msgbox Text_RepelWoreOffUseAnother, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_RepelWoreOffEnd
EventScript_ChooseRepel::
	message Text_UseWhichRepel
	waitmessage
	multichoice 18, 5, MULTICHOICE_REPELS, FALSE
	switch VAR_RESULT
	case 0, EventScript_ChoseRepel
	case 1, EventScript_ChoseSuperRepel
	case 2, EventScript_ChoseMaxRepel
	goto EventScript_RepelWoreOffEnd
	end

EventScript_ChoseRepel::
	setvar VAR_0x8004, ITEM_REPEL
	goto EventScript_UseChosenRepel
	end

EventScript_ChoseSuperRepel::
	setvar VAR_0x8004, ITEM_SUPER_REPEL
	goto EventScript_UseChosenRepel
	end

EventScript_ChoseMaxRepel::
	setvar VAR_0x8004, ITEM_MAX_REPEL
EventScript_UseChosenRepel::
	bufferitemname STR_VAR_2, VAR_0x8004
	checkitem VAR_0x8004, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_NoneOfThatRepel
	special UseRepelFromScript
	playse SE_REPEL
	waitse
	msgbox Text_PlayerUsedRepel
EventScript_RepelWoreOffEnd::
	closemessage
	releaseall
	end

EventScript_NoneOfThatRepel::
	msgbox Text_DontHaveAnyRepel
	goto EventScript_ChooseRepel
	end

Text_RepelWoreOff::
	.string "REPEL's effect wore off…$"

Text_RepelWoreOffUseAnother::
	.string "REPEL's effect wore off…\n"
	.string "Use another?$"

Text_UseWhichRepel::
	.string "Which one will you use?$"

Text_PlayerUsedRepel::
	.string "{PLAYER} used the\n"
	.string "{STR_VAR_2}.$"

Text_DontHaveAnyRepel::
	.string "You don't have any\n"
	.string "{STR_VAR_2}.$"
