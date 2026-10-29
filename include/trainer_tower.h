#ifndef GUARD_TRAINER_TOWER_H
#define GUARD_TRAINER_TOWER_H

struct TrainerTower;

struct TrainerTower *GetTrainerTowerRecord(u32 challengeType);
struct TrainerTower *GetCurrentTrainerTowerRecord(void);
void PrintTrainerTowerRecords(void);
void InitTrainerTowerBattleStruct(void);
void FreeTrainerTowerBattleStruct(void);
u8 GetTrainerTowerTrainerFrontSpriteId(void);
void ResetTrainerTowerResults(void);
void GetTrainerTowerOpponentWinText(u8 *dest, u8 opponentIdx);
void GetTrainerTowerOpponentLoseText(u8 *dest, u8 opponentIdx);
void GetTrainerTowerOpponentName(u8 *text);
u8 GetTrainerTowerOpponentClass(void);

#endif //GUARD_TRAINER_TOWER_H
