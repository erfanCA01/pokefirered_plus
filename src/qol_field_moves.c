#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "item.h"
#include "party_menu.h"
#include "pokemon.h"
#include "script.h"
#include "qol_field_moves.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/qol_field_moves.h"

// Returns the HM item that teaches the given move, or ITEM_NONE.
static u16 GetHmItemForMove(u16 move)
{
    u16 item;

    for (item = ITEM_HM01; item <= ITEM_HM08; item++)
    {
        if (ItemIdToBattleMoveId(item) == move)
            return item;
    }
    return ITEM_NONE;
}

// TRUE if the Pokemon does not need to know the move: the matching HM is in the bag and the
// Pokemon is compatible with it.
bool8 QolMonCanUseFieldMove(struct Pokemon *mon, u16 move)
{
#if QOL_FIELD_MOVES
    u16 item = GetHmItemForMove(move);

    return item != ITEM_NONE && CheckBagHasItem(item, 1) && CanMonLearnTMHM(mon, item - ITEM_TM01);
#else
    return FALSE;
#endif
}

// Returns the party index of a Pokemon that can perform the given field move without
// knowing it (the matching HM is in the bag and the Pokemon is compatible with it),
// or PARTY_SIZE if there is none. The live follower is preferred so it can animate the move.
u8 QolFindFieldMoveUser(u16 move)
{
#if QOL_FIELD_MOVES
    u8 i;
    struct Pokemon *follower;

    if (GetHmItemForMove(move) == ITEM_NONE || !CheckBagHasItem(GetHmItemForMove(move), 1))
        return PARTY_SIZE;

    follower = GetFirstLiveFollowMon();
    if (follower != NULL && QolMonCanUseFieldMove(follower, move))
        return follower - gPlayerParty;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) == SPECIES_NONE)
            break;
        if (QolMonCanUseFieldMove(&gPlayerParty[i], move))
            return i;
    }
#endif
    return PARTY_SIZE;
}

// callfunc: writes the QOL_AUTO_* mode to the given script variable.
bool8 ScrFunc_QolAutoUseMode(struct ScriptContext *ctx)
{
    u16 *var = GetVarPointer(ScriptReadHalfword(ctx));

    if (var == NULL)
        return FALSE;
#if QOL_FIELD_MOVES
    *var = QOL_FIELD_MOVES_NO_MESSAGING ? QOL_AUTO_SILENT : QOL_AUTO_MSG;
#else
    *var = QOL_AUTO_OFF;
#endif
    return FALSE;
}
