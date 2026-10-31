ThreeIsland_House3_MapScripts::
	.byte 0

ThreeIsland_House3_EventScript_Beauty::
	lock
	faceplayer
	msgbox ThreeIsland_House3_Text_WantedToLiveSomewhereQuiet
	goto_if_questlog EventScript_ReleaseEnd
	msgbox ThreeIsland_House3_Text_IGrowHoennBerries, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ThreeIsland_House3_EventScript_DeclineBerries
ThreeIsland_House3_EventScript_ChooseBerry::
	message ThreeIsland_House3_Text_WhichBerry
	waitmessage
	setvar VAR_0x8004, LISTMENU_EV_BERRIES
	special ListMenu
	waitstate
	goto_if_ge VAR_RESULT, 6, ThreeIsland_House3_EventScript_DeclineBerries
	copyvar VAR_0x8008, VAR_RESULT
	addvar VAR_0x8008, ITEM_POMEG_BERRY
	bufferitemname STR_VAR_1, VAR_0x8008
	message ThreeIsland_House3_Text_HowWillYouPay
	waitmessage
	multichoice 17, 4, MULTICHOICE_BERRY_PAYMENT, FALSE
	switch VAR_RESULT
	case 0, ThreeIsland_House3_EventScript_PayPowder
	case 1, ThreeIsland_House3_EventScript_PayTinyMushroom
	case 2, ThreeIsland_House3_EventScript_PayBigMushroom
	goto ThreeIsland_House3_EventScript_DeclineBerries
	end

ThreeIsland_House3_EventScript_PayPowder::
	setvar VAR_0x8004, 100
	specialvar VAR_RESULT, Script_HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, ThreeIsland_House3_EventScript_NotEnoughPowder
	setvar VAR_0x8009, 1
	checkitemspace VAR_0x8008, VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, ThreeIsland_House3_EventScript_NoRoomForBerries
	setvar VAR_0x8004, 100
	special Script_TakeBerryPowder
	goto ThreeIsland_House3_EventScript_GiveBerries
	end

ThreeIsland_House3_EventScript_PayTinyMushroom::
	setvar VAR_0x8009, 1
	setvar VAR_0x800A, ITEM_TINY_MUSHROOM
	goto ThreeIsland_House3_EventScript_PayMushroom
	end

ThreeIsland_House3_EventScript_PayBigMushroom::
	setvar VAR_0x8009, 5
	setvar VAR_0x800A, ITEM_BIG_MUSHROOM
ThreeIsland_House3_EventScript_PayMushroom::
	checkitem VAR_0x800A, 1
	goto_if_eq VAR_RESULT, FALSE, ThreeIsland_House3_EventScript_NoMushroom
	checkitemspace VAR_0x8008, VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, ThreeIsland_House3_EventScript_NoRoomForBerries
	removeitem VAR_0x800A, 1
ThreeIsland_House3_EventScript_GiveBerries::
	giveitem VAR_0x8008, VAR_0x8009
	msgbox ThreeIsland_House3_Text_AnythingElse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ThreeIsland_House3_EventScript_ChooseBerry
	msgbox ThreeIsland_House3_Text_TakeGoodCare
	release
	end

ThreeIsland_House3_EventScript_NotEnoughPowder::
	msgbox ThreeIsland_House3_Text_NotEnoughPowder
	release
	end

ThreeIsland_House3_EventScript_NoMushroom::
	bufferitemname STR_VAR_2, VAR_0x800A
	msgbox ThreeIsland_House3_Text_YouDontHaveAny
	release
	end

ThreeIsland_House3_EventScript_NoRoomForBerries::
	msgbox ThreeIsland_House3_Text_NoRoomForBerries
	release
	end

ThreeIsland_House3_EventScript_DeclineBerries::
	msgbox ThreeIsland_House3_Text_EnjoyingTheQuiet
	release
	end
