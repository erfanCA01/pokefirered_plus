# Pokémon FireRed and LeafGreen: Quality of Life (`qol` branch)

This branch of [pokefirered_plus](https://github.com/erfanCA01/pokefirered_plus) adds quality-of-life improvements
to FireRed and LeafGreen. Some are backported from community tutorials for
[pret/pokeemerald](https://github.com/pret/pokeemerald) (the pokeemerald wiki, and the ghoulslash, SBird1337 and
LOuroboros feature branches) and from [Bruhcation/pokefireredlegacy](https://github.com/Bruhcation/pokefireredlegacy).
All of them were reworked so that saves and link play stay compatible with the unmodified games.

**Based on upstream [pret/pokefirered](https://github.com/pret/pokefirered) commit
[`ce6406d8c2eaf46d543c8a2606de0c3cb1951982`](https://github.com/pret/pokefirered/commit/ce6406d8c2eaf46d543c8a2606de0c3cb1951982)**
("Fix Various Doubles-related AI Bugs (#772)").

## Features

### Bag, PC and items

- **Bag sorting**: a SORT action in the Items and Poké Balls pockets sorts by TYPE, NAME or AMOUNT, in either direction.
- **Register Key Items to L and R** as well as SELECT, in the LR button mode (in L=A mode only R is free). The bag shows
  an L/R marker next to registered items. HELP mode keeps L/R for the Help System, as in vanilla.
- **Prompt to use another Repel** when one wears off and you still have Repels: pick the next one from a list.
- **Repeated field medicine**: after using a medicine (HP, status, revives, vitamins) or an EV-lowering berry, the party
  menu stays open while you still have that item, instead of returning to the bag.
- **Bill's PC**: MOVE POKéMON is the first option and MOVE ITEMS the second. **Player's PC**: SORT ITEMS (by TYPE, NAME or
  AMOUNT) follows DEPOSIT ITEM.
- **Gen 6 style Exp. Share**: USE on an EXP. SHARE in the bag turns it on or off. While it is on and an EXP. SHARE is in
  the bag, the benched party members that can gain EXP (no Eggs, fainted or level 100 Pokémon) split half the EXP, as
  if each held one. The rest of the party gets one combined message. The item can still be held as in vanilla.

### Pokémon and battles

- **Summary screen**: on the POKéMON SKILLS page, A cycles the stat column between ALL, EVs and IVs. In ALL, stats raised
  by the nature are red and lowered ones blue.
- **Hidden Power** shows its real type and power in the summary screen, and **Return / Frustration** show their real
  power.
- **Catch EXP** (Gen 6+): catching a wild Pokémon gives EXP as if it had been defeated.
- **Move Relearner** also teaches moves the Pokémon's pre-evolutions could learn.
- **Repeatable move tutors**: every one-time tutor except the Cape Brink tutor can teach its move again. Mimic only takes
  a POKé DOLL the first time.
- **Party menu**: SELECT works as SWITCH, shown by a "SELECT SWITCH" tab in the corner.
- **Opponent trainers throw their Poké Ball** in an arc, like the player, instead of dropping it.

### World

- **Indoor running**, except in Gyms, the Elite Four rooms, the Champion's room and the Hall of Fame.
- **Renewable one-time TMs and EV berries**:
  - The Silph Co. 11F secretary replicates any one-time TM you have already found, for money.
  - In Celadon, the restaurant's coin-case man sells the same TMs and Emerald's EV-lowering berries for Game Corner coins,
    after the Earth Badge.
  - A Three Island resident grows EV berries in exchange for Berry Powder or mushrooms.
  - Silph Co. 11F gets a pair of warp pads between the elevator and the secretary, active once TEAM ROCKET is beaten.
- **More Poké Balls**:
  - Buying POKé BALLs gives one free PREMIER BALL per 10 bought.
  - The Seven Island Mart sells LUXURY BALLs after Selphy is rescued.
  - The Six Island Mart sells NEST BALLs, and the Four Island Mart sells NET and DIVE BALLs.
- **Post-game gym leader rematches** against all 8 Kanto leaders, Giovanni included, with new teams and dialogue. Each
  leader offers a rematch after the Hall of Fame, once their FAME CHECKER entry is complete. Each rematch can be won once
  per Hall of Fame entry.

### Performance

- **WaitForVBlank halts the CPU** instead of busy-waiting, for lower CPU use and much faster emulator fast-forward. The
  busy-wait is kept while a cable or wireless link is open, so link timing stays vanilla.
- **Union Room check only with a Wireless Adapter**: entering a Pokémon Center no longer hitches when no adapter is
  connected.
- **Constant weather gamma tables** replace `BuildGammaShiftTables`, saving 1,216 bytes of EWRAM.

## Compatibility

- **Saves** are interchangeable with the unmodified FireRed / LeafGreen rev1 ROM in both directions, as often as you
  like. See [Save modifications](#save-modifications) for every save-related change.
- **Link play** (trades, Cable Club battles, Union Room) works with unmodified ROMs. No link-transmitted structure, link
  protocol or `LinkPlayer` data is changed. Battle calculations stay vanilla. The summary-screen values are display only.
- The pret `BUGFIX` and `UBFIX` blocks are left as upstream has them (off in agbcc builds), and no QoL change overrides
  them.
- The ROM header title and game code are unchanged, so the game still identifies itself as FireRed / LeafGreen.

## Save modifications

The save layout is not changed: every save struct keeps its vanilla size and field offsets, so the sector checksums
match. QoL data only uses bytes that vanilla saves and loads but never reads or writes, so vanilla keeps them untouched.
`gSaveBlock1` (`0x0202552C`) and `gPlayerParty` (`0x02024284`) stay at their vanilla rev1 addresses.

### New data in unused save bytes

| Data | Save location | Vanilla meaning | Code | Reset on New Game |
|---|---|---|---|---|
| `registeredItemL`, `registeredItemR` (Register to L / R) | SaveBlock1 `0x0632` and `0x0634`, 2 bytes each | first 4 bytes of `unused_632[6]`, never referenced | `include/global.h` (field split), `src/item_menu.c`, `src/item.c`, `src/new_game.c` | `ClearSav1()` and `src/new_game.c` |
| `FLAG_EXP_SHARE_ON` (Exp. Share on / off) | flag `0x4A8`: SaveBlock1 `0x0F74`, bit 7 | `FLAG_UNUSED_0x4A7`, an unused hidden-item flag | `include/constants/flags.h`, `src/item_use.c`, `src/battle_script_commands.c` | `ClearSav1()` |
| Gym leader rematch won (Brock, Misty, Lt. Surge) | trainer flags `0x51B`-`0x51D`: SaveBlock1 `0x0F83`, bits 3-5 | trainer flags of unused Ruby/Sapphire leader slots 27-29 | `include/constants/opponents.h`, `src/data/trainers.h`, the gym scripts | `ClearSav1()`. Also cleared on every Hall of Fame entry by `EventScript_ResetGymLeaderRematches` (`data/scripts/gym_leader_rematch.inc`) |
| Gym leader rematch won (Erika, Koga, Sabrina, Blaine, Giovanni) | trainer flags `0x552`-`0x556`: SaveBlock1 `0x0F8A`, bits 2-6 | trainer flags of unused Ruby/Sapphire leader slots 82-86 | same | same |

- **Vanilla → QoL**: all of these are 0 in a vanilla save, which means "nothing registered", "Exp. Share off" and
  "every rematch available". No migration is needed.
- **QoL → vanilla → QoL**: vanilla ignores these bits and writes them back unchanged, so L/R registrations, the
  Exp. Share setting and won rematches survive the round trip. A registered item that left the bag meanwhile is cleared
  on the first L/R press.
- Build-time guards: `STATIC_ASSERT`s in `src/item.c` check `sizeof(struct SaveBlock1) == 0x3D68` and the
  `registeredItemL/R` offsets.

### Changes to existing vanilla save data

| Change | Code | Effect in vanilla |
|---|---|---|
| `FLAG_HIDE_VIRIDIAN_GIOVANNI` (`0x055`) is cleared when entering Viridian Gym after the Hall of Fame, so Giovanni is back for his rematch | `data/maps/ViridianCity_Gym/scripts.inc` (`ViridianCity_Gym_OnTransition`) | Giovanni stands in his Gym, says his vanilla farewell and hides himself again. Harmless. |
| The Quest Log (saved) records a rematch win under the **original** leader's trainer ID | `src/quest_log_battle.c` (`GetQuestLogTrainerId`) | Vanilla playback shows "defeated BROCK" and never the unused slot's name. |
| Bag sorting and PC SORT ITEMS reorder slots inside the existing bag pockets and `pcItems[30]` | `src/item.c`, `src/item_menu.c`, `src/player_pc.c` | Vanilla loads any slot order. |
| Repeatable move tutors set the vanilla `FLAG_TUTOR_*` exactly when vanilla does | `data/scripts/move_tutors.inc` | None. |

### What is deliberately not saved

- **Repel prompt**: it uses the vanilla `VAR_REPEL_STEP_COUNT`, and nothing about the last-used Repel is saved.
- **Renewable TM and berry shops**: they are run by existing vanilla NPCs, with no new object events or map layout
  changes. A new NPC saved on its map would have no script in vanilla and could crash when talked to.
- **Gym leader rematch trainers**: they reuse leftover trainer slots, so no trainer data is added to the save.
- Summary-screen modes, PC menu state and the Exp. Share message pass are RAM-only (`BattleStruct`'s unused `field_11`
  holds the pass).

## Building

1. Set up the build environment and install agbcc, as described in [INSTALL.md](INSTALL.md). This branch uses the
   original agbcc compiler.
2. Build both ROMs from the repository root:

   ```
   make -j$(nproc) firered_rev1 leafgreen_rev1
   ```

   This produces `pokefirered_qol_rev1.gba` and `pokeleafgreen_qol_rev1.gba`. The other upstream targets (`firered`,
   `leafgreen`, `firered_switch`, ...) are also available and get the same `_qol` name, but the rev1 ROMs are the ones
   that were tested. These ROMs are modified, so they will not match the original sha1s listed below, and
   `make compare_*` does not apply.
3. `make tidy` removes the built ROMs and the build folder.

---

## Upstream: Pokémon FireRed and LeafGreen

This is a decompilation of English Pokémon FireRed and LeafGreen.

It builds the following ROM images:

* [**pokefirered.gba**](https://datomatic.no-intro.org/?page=show_record&s=23&n=1616) `sha1: 41cb23d8dccc8ebd7c649cd8fbb58eeace6e2fdc`
* [**pokeleafgreen.gba**](https://datomatic.no-intro.org/?page=show_record&s=23&n=1617) `sha1: 574fa542ffebb14be69902d1d36f1ec0a4afd71e`
* [**pokefirered_rev1.gba**](https://datomatic.no-intro.org/?page=show_record&s=23&n=1672) `sha1: dd5945db9b930750cb39d00c84da8571feebf417`
* [**pokeleafgreen_rev1.gba**](https://datomatic.no-intro.org/index.php?page=show_record&s=23&n=1668) `sha1: 7862c67bdecbe21d1d69ce082ce34327e1c6ed5e`
* [**pokefirered_switch.gba**](https://datomatic.no-intro.org/index.php?page=show_record&s=23&n=x550) `sha1: baa452d0b24629dd7782cfc07a8984085dde1311`
* [**pokeleafgreen_switch.gba**](https://datomatic.no-intro.org/index.php?page=show_record&s=23&n=x551) `sha1: 62b9fc77549dbc67032eb6cbd0ea6ad3b825690f`

To set up the repository, see [INSTALL.md](INSTALL.md).

For contacts and other pret projects, see [pret.github.io](https://pret.github.io/).
