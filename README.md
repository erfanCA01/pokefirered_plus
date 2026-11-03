# Pokémon FireRed and LeafGreen: e-Reader restoration (`ecard` branch)

This branch of [pokefirered_plus](https://github.com/erfanCA01/pokefirered_plus) restores the e-Reader content that was cut
from the non-Japanese releases of FireRed and LeafGreen. It is a source reconstruction of the RestorationProject
e-Reader patch (published on Project Pokémon as a BPS patch, with no source). The patch was first rebuilt in this decomp
byte-for-byte, then changed so that saves stay compatible with the unmodified game.

**Based on upstream [pret/pokefirered](https://github.com/pret/pokefirered) commit
[`ce6406d8c2eaf46d543c8a2606de0c3cb1951982`](https://github.com/pret/pokefirered/commit/ce6406d8c2eaf46d543c8a2606de0c3cb1951982)**
("Fix Various Doubles-related AI Bugs (#772)").

## Features

- **e-Reader card scanning.** Choosing MYSTERY GIFT on the main menu with no Wireless Adapter attached opens the e-Reader
  screen instead of the "no adapter" error. It talks to an **English** e-Reader: the handshake, the program uploaded to
  the e-Reader and the e-Reader / Mystery Event texts are all localized. MYSTERY GIFT is unlocked as in vanilla, by entering
  "LINK TOGETHER WITH ALL" in the survey at any Poké Mart counter.
- **e-Reader Trainer Tower.** Scanned Trainer Tower cards (up to 8, one per floor) put new trainers in the Trainer Tower on
  Seven Island, with new prizes for clearing it in the target time. e-Reader trainer names are copied in full (8 characters).
- **Trainer Tower mode menu.** The receptionist offers SINGLE / DOUBLE / KNOCKOUT / MIXED / E-READER / EXIT:
  - The four vanilla modes are the vanilla challenge (8 floors, vanilla trainers, their own records).
  - E-READER uses the scanned cards and tells you how many floors there are ("up to Floor N") after you pick it.
    With no card scanned, she says no e-Reader trainers are available and returns to the menu.
- **E-READER row on the Time Board**, with its own best time.
- The card `.raw` files are not part of this repository. A localized set is included in the RestorationProject download
  (`Card Files` folder). In mGBA, link two GBA instances, load an English e-Reader on one side, then scan the cards.

## Compatibility

- **Saves** are interchangeable with the unmodified FireRed / LeafGreen rev1 ROM in both directions, as often as you
  like (tested with an 80+ hour save). The e-Reader best time even survives a round trip through vanilla. See
  [Save modifications](#save-modifications) for exactly what is written where.
- **Link play** (trades, Cable Club battles, Union Room) works with unmodified ROMs. The only link change is the
  GBA ↔ e-Reader handshake value (`0xCCD0` → `0xCCC0`, the English e-Reader's). No `LinkPlayer` data, link-transmitted
  structure or GBA ↔ GBA protocol is changed.
- **Unlike the original BPS patch.** The RestorationProject patch grows `SaveBlock1` by 12 bytes, which changes the save
  checksum, so a save it writes is reported as deleted by vanilla. This branch does not have that problem.
- The pret `BUGFIX` and `UBFIX` fixes are always enabled (`include/global.h`).

## Save modifications

`sizeof(struct SaveBlock1)` stays `0x3D68`, the same as vanilla (enforced by a `STATIC_ASSERT` in `include/global.h`).
The save sector layout, sector sizes and checksums are not changed, and neither are `SaveBlock2` and the Pokémon
storage. All new data is in space vanilla never reads or writes:

| What | Where in the save | Size | Vanilla use of that space | What vanilla does with it |
|---|---|---|---|---|
| e-Reader Trainer Tower record (`trainerTowerEReader`, a `struct TrainerTower`: timer, best time, floors cleared, prize/status bits) | `SaveBlock1` + `0x3D24`-`0x3D2F` | 12 bytes | `unused_3D24[16]`, never touched | Ignores it, so the record is kept across a vanilla round trip |
| Key the e-Reader best time is encrypted with (`trainerTowerEReaderKey`) | `SaveBlock1` + `0x3D30`-`0x3D33` | 4 bytes | rest of `unused_3D24[16]` | Ignores it. Vanilla changes the save's encryption key without knowing about this record, so this build re-keys the record the next time it reads it |
| "Current run is an e-Reader run" (`FLAG_TRAINER_TOWER_EREADER`, flag `0x0AF`) | `SaveBlock1.flags` (`+ 0x0EE0`), byte `+ 0x0EF5`, bit 7 | 1 bit | `FLAG_0x0AF`, unused | Ignores it. It is cleared when you return to the Trainer Tower counter |
| Scanned e-Reader Trainer Tower cards | Save sectors 30 and 31 (`SECTOR_ID_TRAINER_TOWER_1/2`) | 2 sectors | Same purpose: vanilla reserves them for e-Reader Trainer Tower data (used by the Japanese release) | Keeps them. The English vanilla game cannot reach its e-Reader code, so the data is simply not used |

Values written to existing vanilla fields stay within the range vanilla expects:

| Field | Where | Rule |
|---|---|---|
| `towerChallengeId` | `SaveBlock1` + `0x3D34` | Always 0-3 (a vanilla mode). An e-Reader run is marked by the flag above, not by a 5th challenge type, because vanilla uses this value as an unchecked index into `trainerTower[4]`. An out-of-range value left by an older build of this branch is reset when the Trainer Tower code runs. |
| `trainerTower[4]` | `SaveBlock1` + `0x3D38`-`0x3D67` | Only the 4 vanilla challenge types, as in vanilla. |

What you lose when you play the save on vanilla: nothing is lost or reset. The e-Reader floors simply are not available
there, and vanilla's Trainer Tower runs its normal 8 floors.

## Building

1. Set up the build environment and install agbcc, as described in [INSTALL.md](INSTALL.md). This branch uses the
   original agbcc compiler.
2. Build both ROMs from the repository root:

   ```
   make -j$(nproc) firered_rev1 leafgreen_rev1
   ```

   This produces `pokefirered_rev1_ecard.gba` and `pokeleafgreen_rev1_ecard.gba`. The other upstream targets
   (`firered`, `leafgreen`, `firered_rev10`, ...) are also available and get the same `_ecard` suffix, but the rev1
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
