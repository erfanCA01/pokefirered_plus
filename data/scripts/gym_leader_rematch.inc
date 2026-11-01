@ Post-game gym leader rematches. A leader offers one after the Hall of Fame once
@ their FAME CHECKER entry is complete. Each rematch can be won once per Hall of
@ Fame entry: the rematch trainers reuse the unused RS leader slots, whose trainer
@ flags vanilla never touches, and EventScript_SetDefeatedEliteFourFlagsVars
@ clears them again.

@ Input: VAR_0x8004 = FAMECHECKER_* person, VAR_0x8005 = rematch trainer
@ Output: VAR_RESULT = TRUE if the player accepted the rematch
EventScript_TryGymLeaderRematch::
	specialvar VAR_RESULT, HasUnlockedAllFlavorTextsForSpecialVar
	goto_if_eq VAR_RESULT, FALSE, EventScript_GymLeaderRematchNotReady
	checktrainerflag VAR_0x8005
	goto_if TRUE, EventScript_GymLeaderRematchAlreadyWon
	msgbox Text_GymLeaderRematchOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_GymLeaderRematchDeclined
	return

EventScript_GymLeaderRematchNotReady::
	msgbox Text_GymLeaderRematchNotReady
	setvar VAR_RESULT, FALSE
	return

EventScript_GymLeaderRematchAlreadyWon::
	msgbox Text_GymLeaderRematchAlreadyWon
	setvar VAR_RESULT, FALSE
	return

EventScript_GymLeaderRematchDeclined::
	msgbox Text_GymLeaderRematchDeclined
	setvar VAR_RESULT, FALSE
	return

EventScript_ResetGymLeaderRematches::
	cleartrainerflag TRAINER_LEADER_BROCK_REMATCH
	cleartrainerflag TRAINER_LEADER_MISTY_REMATCH
	cleartrainerflag TRAINER_LEADER_LT_SURGE_REMATCH
	cleartrainerflag TRAINER_LEADER_ERIKA_REMATCH
	cleartrainerflag TRAINER_LEADER_KOGA_REMATCH
	cleartrainerflag TRAINER_LEADER_SABRINA_REMATCH
	cleartrainerflag TRAINER_LEADER_BLAINE_REMATCH
	cleartrainerflag TRAINER_LEADER_GIOVANNI_REMATCH
	return

Text_GymLeaderRematchOffer::
    .string "Welcome back, {PLAYER}!\n"
    .string "Or should I say, CHAMPION!\p"
    .string "I've trained hard since our\n"
    .string "last battle.\p"
    .string "Will you take on my full power\n"
    .string "in a rematch?$"

Text_GymLeaderRematchNotReady::
    .string "Congratulations on becoming the\n"
    .string "CHAMPION, {PLAYER}!\p"
    .string "I'd like a rematch someday, but\n"
    .string "I'm not ready yet.\p"
    .string "In the meantime, why not learn\n"
    .string "all about me with your\l"
    .string "FAME CHECKER?$"

Text_GymLeaderRematchAlreadyWon::
    .string "That was a great battle!\p"
    .string "Prove yourself at the POKéMON\n"
    .string "LEAGUE again, and I'll be ready\l"
    .string "for another rematch!$"

Text_GymLeaderRematchDeclined::
    .string "I see...\n"
    .string "Come back whenever you're ready.$"
