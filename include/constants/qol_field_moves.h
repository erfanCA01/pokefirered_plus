#ifndef GUARD_CONSTANTS_QOL_FIELD_MOVES_H
#define GUARD_CONSTANTS_QOL_FIELD_MOVES_H

// QoL field moves (backport idea from PokemonSanFran's pokeemerald qol_field_moves,
// reduced to what FireRed needs: no tool items, no new flags/vars -> save compatible).
//
// When QOL_FIELD_MOVES is TRUE, a field move (Cut, Surf, Strength, Rock Smash,
// Waterfall) can be used by interacting with its obstacle as long as
//   - the matching HM is in the bag,
//   - the badge is owned (checked by the existing scripts / C code), and
//   - a party Pokemon either knows the move or is able to learn it through the HM.
// The HM never has to be taught. The yes/no prompt is skipped.
// Set to FALSE to get the unmodified vanilla behavior.
#define QOL_FIELD_MOVES TRUE

// When TRUE (and QOL_FIELD_MOVES is TRUE) the "<MON> used <MOVE>!" text is skipped as well;
// only the field move animation plays.
#define QOL_FIELD_MOVES_NO_MESSAGING FALSE

// Fly and Flash also get a party menu entry for a Pokemon that is compatible with the HM
// (HM02/HM05 in the bag) even if it does not know the move. Both are only ever started from the
// party menu; nothing is triggered automatically.

// The scripts (data/scripts/field_moves.inc, surf.inc) pick the prompt/text with assembler .if blocks,
// so these must stay plain TRUE/FALSE.

#endif // GUARD_CONSTANTS_QOL_FIELD_MOVES_H
