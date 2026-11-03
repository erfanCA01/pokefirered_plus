@ Post-game gym leader rematches. A leader offers one after the Hall of Fame once
@ their FAME CHECKER entry is complete. Each rematch can be won once per Hall of
@ Fame entry: the rematch trainers reuse the unused RS leader slots, whose trainer
@ flags vanilla never touches, and EventScript_SetDefeatedEliteFourFlagsVars
@ clears them again. Each gym script checks this itself, with the leader's own texts.

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
