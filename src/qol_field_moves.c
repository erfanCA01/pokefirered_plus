#include "global.h"
#include "event_object_movement.h"
#include "item.h"
#include "party_menu.h"
#include "pokemon.h"
#include "qol_field_moves.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/qol_field_moves.h"

// The prompt/text part of QoL field moves is chosen at build time in the scripts
// (data/scripts/field_moves.inc, surf.inc); this file only finds a Pokemon that can use the move.

#if QOL_FIELD_MOVES
// Returns the HM that teaches the given move if it is in the bag, or ITEM_NONE.
static u16 GetHmInBagForMove(u16 move)
{
    u16 item;

    for (item = ITEM_HM01; item <= ITEM_HM08; item++)
    {
        if (ItemIdToBattleMoveId(item) == move)
            return CheckBagHasItem(item, 1) ? item : ITEM_NONE;
    }
    return ITEM_NONE;
}
#endif

// TRUE if the Pokemon does not need to know the move: the matching HM is in the bag and the
// Pokemon is compatible with it.
bool8 QolMonCanUseFieldMove(struct Pokemon *mon, u16 move)
{
#if QOL_FIELD_MOVES
    u16 item = GetHmInBagForMove(move);

    return item != ITEM_NONE && CanMonLearnTMHM(mon, item - ITEM_TM01);
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
    u8 i, tm;
    u16 item = GetHmInBagForMove(move);
    struct Pokemon *follower;

    if (item == ITEM_NONE)
        return PARTY_SIZE;
    tm = item - ITEM_TM01;

    follower = GetFirstLiveFollowMon();
    if (follower != NULL && CanMonLearnTMHM(follower, tm))
        return follower - gPlayerParty;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) == SPECIES_NONE)
            break;
        if (CanMonLearnTMHM(&gPlayerParty[i], tm))
            return i;
    }
#endif
    return PARTY_SIZE;
}
