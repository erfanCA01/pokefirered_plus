# Pokémon FireRed and LeafGreen: Following Pokémon (`followers` branch)

This branch of [pokefirered_plus](https://github.com/erfanCA01/pokefirered_plus) adds following Pokémon to
FireRed and LeafGreen. It is a backport of the [`followers-expanded-id`](https://github.com/aarant/pokeemerald/tree/followers-expanded-id) feature from
[aarant/pokeemerald](https://github.com/aarant/pokeemerald), plus a few
optional quality-of-life field move changes.

**Based on upstream [pret/pokefirered](https://github.com/pret/pokefirered) commit
[`ce6406d8c2eaf46d543c8a2606de0c3cb1951982`](https://github.com/pret/pokefirered/commit/ce6406d8c2eaf46d543c8a2606de0c3cb1951982)**
("Fix Various Doubles-related AI Bugs (#772)").

## Features

- The first healthy party Pokémon follows the player, with its own overworld sprite (shiny colors included). It comes
  out of its Poké Ball, has emotes and messages when you talk to it, and performs Cut, Rock Smash, Surf and Fly itself
  when it is the one using the move.
- The follower is hidden where it does not fit: inside small buildings if it is too big, in elevators, on the Trainer
  Tower floors, in link rooms, in the Safari Zone and while the Quest Log replays.
- In single battles, the following or surfing Pokémon slides in and out instead of being thrown from a ball.
- Optional QoL field moves (on by default, see below).

## Compatibility

- **Saves** are interchangeable with the unmodified FireRed / LeafGreen ROM in both directions, as often as you like.
- **Link play** (trades, Cable Club battles, Union Room) works with unmodified ROMs.
- The original game assets, including the existing overworld sprites, are unchanged.
- The pret `BUGFIX` and `UBFIX` fixes are always enabled (`include/global.h`).
- FireRed has no real-time clock, so time-of-day follower messages are disabled.

## Configuration

All options are compile-time `#define`s. Change one and rebuild. None of them change the save layout or link data.

### QoL field moves: `include/constants/qol_field_moves.h`

| Option | Default | Effect |
|---|---|---|
| `QOL_FIELD_MOVES` | `TRUE` | Cut, Rock Smash, Strength, Surf and Waterfall work on their obstacle with no yes/no prompt, as long as the HM is in the bag, the badge is owned and a party Pokémon knows the move or can learn it from the HM (it does not have to be taught). A compatible Pokémon also gets FLY / FLASH in its party menu. `FALSE` gives the vanilla behavior (with QoL off, the scripts are byte-identical to vanilla). |
| `QOL_FIELD_MOVES_NO_MESSAGING` | `FALSE` | With `QOL_FIELD_MOVES` on, also skips the "<POKéMON> used <MOVE>!" text, so only the animation plays. |

### Following Pokémon: `include/constants/event_objects.h`

| Option | Default | Effect |
|---|---|---|
| `OW_MON_BOBBING` | `TRUE` | Overworld Pokémon bob up and down while idle and walking. |
| `OW_MON_WANDER_WALK` | `TRUE` | Wandering overworld Pokémon walk in place while paused between steps instead of standing still. |
| `OW_MON_POKEBALLS` | `TRUE` | The follower comes out of the ball it was caught in instead of a regular Poké Ball. |
| `OW_MON_SCRIPT_MOVEMENT` | `TRUE` | Scripts handle the follower: it is hidden when a script would collide with it, and scripted player movement moves it too (`FLAG_SAFE_FOLLOWER_MOVEMENT` on by default). `FALSE`: script collisions are not handled. |
| `LARGE_OW_SUPPORT` | `TRUE` | Support for 48x48 / 64x64 overworld sprites (shadow offsets, elevation and bridge handling). |
| `OW_MON_ALLOWED_SPECIES` | `0` | If set, only this species may follow. Accepts a var, e.g. `VAR_TEMP_1`. `0` = no restriction. |
| `OW_MON_ALLOWED_MET_LVL` | `0` | If set, only Pokémon met at this level may follow. `0` = no restriction. |
| `OW_MON_ALLOWED_MET_LOC` | `MAPSEC_COUNT` | If set, only Pokémon met at this map section may follow. `MAPSEC_COUNT` = no restriction. |

### Graphics: `include/global.h`

| Option | Default | Effect |
|---|---|---|
| `OW_GFX_COMPRESS` | `TRUE` | Overworld graphics, including the follower sprites, are stored compressed in the ROM. |

Each boolean option above builds cleanly when set to `FALSE`, but the defaults are the configuration that was play-tested.

## Building

1. Set up the build environment and install agbcc, as described in [INSTALL.md](INSTALL.md). This branch uses the
   original agbcc compiler.
2. Build both ROMs from the repository root:

   ```
   make -j$(nproc) firered_rev1 leafgreen_rev1
   ```

   This produces `pokefirered_follower_rev1.gba` and `pokeleafgreen_follower_rev1.gba`. The other upstream targets
   (`firered`, `leafgreen`, `firered_rev10`, ...) are also available and get the same `_follower` name, but the rev1
   ROMs are the ones that were tested. These ROMs are modified, so they will not match the original sha1s listed below.
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
