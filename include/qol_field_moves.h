#ifndef GUARD_QOL_FIELD_MOVES_H
#define GUARD_QOL_FIELD_MOVES_H

struct Pokemon;

u8 QolFindFieldMoveUser(u16 move);
bool8 QolMonCanUseFieldMove(struct Pokemon *mon, u16 move);

#endif // GUARD_QOL_FIELD_MOVES_H
