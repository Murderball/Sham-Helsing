# VH_HuntSlice (UE 5.7.x)

A minimal C++-first vertical slice project scaffold for a co-op gothic hunt game.

## Open the project
1. Open `VH_HuntSlice.uproject` with Unreal Engine **5.7.x**.
2. If prompted, generate project files and build `VH_HuntSliceEditor`.
3. Open the editor and create the Blueprint/map assets described in `Docs/Blueprint_Stub_Setup.md`.

## 2-player PIE test
1. Set **Play > Number of Players = 2** and **Net Mode = Play As Listen Server**.
2. Load `Map_MainMenu`.
3. Host on one instance, Join on the other (LAN via `OnlineSubsystemNull`).
4. Verify server travel flow:
   - Main Menu -> BaseHub
   - BaseHub Start Hunt -> Hunt01
   - Hunt outcome -> BaseHub

## Slice includes
- C++ game framework (`AVHGameModeBase`, menu/hub/hunt game modes)
- Replicated `AVHGameState` with base level, currency, intel, unlocked monsters
- Replicated `AVHPlayerState` with role, appearance preset, HP/downed state
- Save/load progression subsystem (`UVHProgressionSubsystem` + `UVHSaveGame`)
- LAN session subsystem (`UVHSessionSubsystem`)
- Monster character with simple chase/attack and win on kill
- Interactable system + clues + base terminal + banish altar + trap actor
- Configured OnlineSubsystemNull and input mappings

## Known limitations
- UMG widgets and map geometry are intentionally placeholder stubs and should be assembled in-editor.
- Monster AI is simple tick-driven pursuit (no Behavior Tree).
- Appearance presets are numeric IDs intended for BP material/mesh switching.
