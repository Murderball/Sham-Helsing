# UE 5.7 Multiplayer Vertical Slice Setup (Sham Helsing)

## Architecture Overview
- **Authoritative server gameplay**: GameMode owns mission flow and travel; GameState replicates party mission state (`TeamIntelCount`, `CurrentMonsterId`, `MissionPhase`, base progression stats).
- **Player identity layer**: PlayerState replicates role, appearance preset, and currency display.
- **Progression & content gating**: `USHProgressionLibrary` contains hard-coded monster data and unlocked-monster calculation from Base Level.
- **Mission loop**: Hub GameMode upgrades base / starts hunts; Hunt GameMode spawns one monster and calculates intel HP modifier.
- **Session layer**: `USessionSubsystem` provides Host/Find/Join LAN flows through OnlineSubsystemNull.

## File Creations/Edits
1. `Source/ShamHelsing/ShamHelsing.h`
2. `Source/ShamHelsing/ShamHelsing.cpp`
3. `Source/ShamHelsing/ShamHelsing.Build.cs`
4. `Source/ShamHelsing/Systems/SHCoreTypes.h`
5. `Source/ShamHelsing/Systems/SG_PlayerProfile.h`
6. `Source/ShamHelsing/Systems/SHProgressionLibrary.h`
7. `Source/ShamHelsing/Systems/SHProgressionLibrary.cpp`
8. `Source/ShamHelsing/Systems/SessionSubsystem.h`
9. `Source/ShamHelsing/Systems/SessionSubsystem.cpp`
10. `Source/ShamHelsing/Gameplay/SHPlayerState.h`
11. `Source/ShamHelsing/Gameplay/SHPlayerState.cpp`
12. `Source/ShamHelsing/Gameplay/SHGameStateBase.h`
13. `Source/ShamHelsing/Gameplay/SHGameStateBase.cpp`
14. `Source/ShamHelsing/Gameplay/HubGameMode.h`
15. `Source/ShamHelsing/Gameplay/HubGameMode.cpp`
16. `Source/ShamHelsing/Gameplay/HuntGameMode.h`
17. `Source/ShamHelsing/Gameplay/HuntGameMode.cpp`
18. `Source/ShamHelsing/Gameplay/SHPlayerCharacter.h`
19. `Source/ShamHelsing/Gameplay/SHPlayerCharacter.cpp`
20. `Source/ShamHelsing/Gameplay/SHIntelActor.h`
21. `Source/ShamHelsing/Gameplay/SHIntelActor.cpp`
22. `Source/ShamHelsing/Gameplay/SHMonsterCharacter.h`
23. `Source/ShamHelsing/Gameplay/SHMonsterCharacter.cpp`
24. `Source/ShamHelsing/UI/SHUIBlueprintLibrary.h`
25. `Source/ShamHelsing/UI/SHUIBlueprintLibrary.cpp`
26. `Config/DefaultEngine.ini`

## Unreal Editor Hookup Steps
1. **Create project**: UE 5.7 → Games → First Person → C++ → Starter Content.
2. **Copy files** in this patch into `Source/ShamHelsing` and `Config`.
3. **Generate project files** and compile C++.
4. **Plugins**: enable OnlineSubsystem, OnlineSubsystemUtils, OnlineSubsystemNull.
5. **Maps**:
   - `Map_MainMenu`: simple floor + Widget with Host/Refresh/Join.
   - `Map_Hub`: basic room, add UI terminal interaction to open HubWidget.
   - `Map_Hunt_01`: blockout arena + 8 placed `BP_SHIntelActor` + patrol points.
   - `Map_Transition`: empty map for seamless travel transitions.
6. **Blueprints** (minimal):
   - Create `BP_SHPlayerCharacter` from `ASHPlayerCharacter`.
   - Create `BP_SHMonsterCharacter` from `ASHMonsterCharacter`.
   - Create `BP_SHIntelActor` from `ASHIntelActor`.
   - Create `BP_HubGameMode` from `AHubGameMode` and set `GameStateClass=ASHGameStateBase`.
   - Create `BP_HuntGameMode` from `AHuntGameMode`, set `MonsterClass=BP_SHMonsterCharacter` and `GameStateClass=ASHGameStateBase`.
7. **Appearance presets (6)**:
   - In `BP_SHPlayerCharacter`, add 6 material instances (different colors) and apply based on replicated `PresetId` from PlayerState.
8. **Role select widget**:
   - Button per role calls `ServerSetRole` on owning PlayerState.
9. **Character creation widget**:
   - 6 buttons call `ServerSetPreset` + save to `USG_PlayerProfile` slot `PlayerProfile_0`.
10. **Hub widget**:
   - Display `BaseLevel`, `TeamCurrency`, unlocked monster list from `USHProgressionLibrary::RecomputeUnlockedMonsters`.
   - Upgrade button calls `ServerUpgradeBase`.
   - Hunt button selects unlocked monster and calls `ServerStartHunt`.
11. **Hunt HUD widget**:
   - Show `TeamIntelCount`, `CurrentMonsterId`, and HP modifier text `Monster HP Scale = max(0.3, 1 - 0.1 * Intel)`.
12. **Intel scan interaction**:
   - Use E key (existing input) to call `Interact()`.
   - UI progress bar duration: `2.0s` (or `1.0s` for Investigator).

## How to Run
1. Open project in UE 5.7.
2. Build C++ (`Development Editor`).
3. Set default map to `Map_MainMenu`.
4. Launch PIE with 2–4 players, Net Mode = Listen Server.
5. Client 1: Host session; Client 2+: Refresh + Join.

## How to Test Replication (Acceptance Checklist)
1. Host/Join into Hub; verify both pawns visible and moving.
2. Choose different appearance presets; confirm remote material color updates.
3. Choose different roles; verify role text/effects differ.
4. Start Hunt from host; all players travel together.
5. Collect intel: one object only collectible once; count updates for all players.
6. Verify monster spawned server-side and HP replicated.
7. Verify intel reduces monster HP by 10% each intel (capped at 30% total HP floor).
8. Finish hunt and verify reward formula (`50 + intel*10 + 50 if killed`) reflected in Hub currency.
9. Upgrade base cost formula (`100 * BaseLevel`), then verify unlocks increase to Wraith/Vampire Spawn.
10. Ensure Hunt monster selection only lists unlocked IDs.

## Notes / Reasonable Decisions
- Intel modifier implemented as **monster max HP reduction** for clear testing.
- Currency/base state is party-shared in GameState for simple co-op slice; host persistence should serialize this to `USG_PlayerProfile` on return to Hub.
- AI is intentionally lightweight (server-side nearest-player chase/melee) to keep implementation stable for 2–4 LAN players.
