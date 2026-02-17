# VHPhasmaSlice (UE 5.7) - Complete Vertical Slice Setup

## A) Project Creation Steps
1. Open **Unreal Engine 5.7** launcher and create a **Games > C++ > First Person** project named `VHPhasmaSlice`.
2. Close the editor.
3. Copy this repository's `Source/`, `Config/`, and `VHPhasmaSlice.uproject` into the new project root.
4. Right-click `VHPhasmaSlice.uproject` and select **Generate Visual Studio project files**.
5. Open `VHPhasmaSlice.sln` in Visual Studio 2022.
6. Build target: **Development Editor | Win64**.
7. Launch Unreal Editor using `VHPhasmaSlice.uproject`.

## B) File Tree

### `/Source`
```text
Source/

  VHPhasmaSlice/
    VHPhasmaSlice.Build.cs
    VHPhasmaSlice.cpp
    VHPhasmaSlice.h

    Core/
      VHGameInstance.h
      VHGameInstance.cpp
      VHTypes.h
    Data/
      MonsterDefinition.h
      RoleDefinition.h
    GameModes/
      VHGameMode_BaseHub.h
      VHGameMode_BaseHub.cpp
      VHGameMode_Mission.h
      VHGameMode_Mission.cpp
      VHGameState.h
      VHGameState.cpp
    Player/
      VHCharacter.h
      VHCharacter.cpp
      VHPlayerController.h
      VHPlayerController.cpp
      VHPlayerState.h
      VHPlayerState.cpp
    AI/
      VHMonsterBase.h
      VHMonsterBase.cpp
      VHMonster_Wraith.h
      VHMonster_Wraith.cpp
      VHMonster_Revenant.h
      VHMonster_Revenant.cpp
    World/
      VHIntelPickup.h
      VHIntelPickup.cpp
      VHMissionDirector.h
      VHMissionDirector.cpp
    UI/
      VHUIBlueprintLibrary.h
      VHUIBlueprintLibrary.cpp
```

### `/Content`
```text
Content/
  Maps/
    L_MainMenu.umap
    L_BaseHub.umap
    L_Mission01.umap
  UI/
    WBP_MainMenu.uasset
    WBP_CharacterCreate.uasset
    WBP_BaseHubHUD.uasset
    WBP_MissionHUD.uasset
  Input/
    IMC_Default.uasset
    IA_Move.uasset
    IA_Look.uasset
    IA_Jump.uasset
    IA_Fire.uasset
  Data/
    Monsters/
      DA_Monster_Wraith.uasset
      DA_Monster_Revenant.uasset
    Roles/
      DA_Role_MonsterHunter.uasset
      DA_Role_Support.uasset
      DA_Role_Analyst.uasset
  Blueprints/
    BP_VHCharacter.uasset
    BP_VHMonster_Wraith.uasset
    BP_VHMonster_Revenant.uasset
    BP_VHIntelPickup.uasset
    BP_VHMissionDirector.uasset
```

## C) C++ Code
All C++ source for this implementation is included in `Source/VHPhasmaSlice/**` exactly as checked into this repo.

## D) Blueprint/DataAsset Creation Steps

### 1. Input (Enhanced Input)
1. Create `Input Action` assets:
   - `IA_Move` Value Type = Axis2D
   - `IA_Look` Value Type = Axis2D
   - `IA_Jump` Value Type = Boolean
   - `IA_Fire` Value Type = Boolean
2. Create `Input Mapping Context` `IMC_Default`.
3. Add mappings:
   - `IA_Move`: W(0,1), S(0,-1), A(-1,0), D(1,0), Gamepad Left Stick
   - `IA_Look`: Mouse X/Y, Gamepad Right Stick
   - `IA_Jump`: Space Bar, Gamepad FaceButton Bottom
   - `IA_Fire`: Left Mouse Button, Gamepad Right Trigger

### 2. Character Blueprint
1. Create BP child: `BP_VHCharacter` from `AVHCharacter`.
2. Set input references:
   - `DefaultContext = IMC_Default`
   - `IA_Move/IA_Look/IA_Jump/IA_Fire` accordingly.
3. Set this BP as default pawn in both game modes (if not already by class defaults).

### 3. Data Assets
Create `Primary Data Asset` from class `MonsterDefinition`:
- `DA_Monster_Wraith`: MonsterId=`Monster_Wraith`, UnlockBaseLevel=1, MaxHealth=140, RewardCurrency=150
- `DA_Monster_Revenant`: MonsterId=`Monster_Revenant`, UnlockBaseLevel=2, MaxHealth=220, RewardCurrency=260

Create `Primary Data Asset` from class `RoleDefinition`:
- `DA_Role_MonsterHunter`: Damage=1.35 Intel=1.0 Support=0.15
- `DA_Role_Support`: Damage=1.0 Intel=1.0 Support=1.0
- `DA_Role_Analyst`: Damage=0.9 Intel=1.5 Support=0.2

### 4. Monster Blueprints
1. `BP_VHMonster_Wraith` child of `AVHMonster_Wraith`, set `Definition=DA_Monster_Wraith`.
2. `BP_VHMonster_Revenant` child of `AVHMonster_Revenant`, set `Definition=DA_Monster_Revenant`.

### 5. Map setup
#### `L_MainMenu`
- Empty floor + PlayerStart.
- Add UI bootstrap BP (Level Blueprint): Create and add `WBP_MainMenu` to viewport.

#### `L_BaseHub`
- Add simple room geometry with cubes.
- GameMode Override: `AVHGameMode_BaseHub`.
- PlayerStart.
- Level Blueprint on BeginPlay adds `WBP_BaseHubHUD`.

#### `L_Mission01`
- Add floor/walls and 3 placed `BP_VHIntelPickup` actors.
- Place one `BP_VHMonster_Wraith` (or Revenant for BaseLevel >=2 tests).
- Place `BP_VHMissionDirector` from `AVHMissionDirector`; set `MissionMonster` reference to the monster actor.
- GameMode Override: `AVHGameMode_Mission`.
- Level Blueprint on BeginPlay adds `WBP_MissionHUD`.

### 6. UMG widgets
#### `WBP_MainMenu`
Buttons:
- `Create Character` -> Open `WBP_CharacterCreate`.
- `Host LAN` -> `GetGameInstance -> HostLANSession`.

- `Quit` -> `QuitGame`.

#### `WBP_CharacterCreate`
- Dropdowns: BodyPreset, HeadPreset, OutfitPreset, Role.
- Confirm:
  1. `GetOwningPlayerState` cast `AVHPlayerState` -> `ServerSetRoleAndCosmetics`.
  2. `GetGameInstance` cast `UVHGameInstance` -> `TravelToHubAfterCharacterCreate`.

#### `WBP_BaseHubHUD`
- Bind text: Currency from local `AVHPlayerState`, BaseLevel from `AVHGameState`.
- `Upgrade Base` button -> `AVHPlayerController::ServerTryUpgradeBase`.
- `Start Mission` button (host only) -> `AVHPlayerController::ServerStartMission`.
- Monster Codex list from two DataAssets + `IsMonsterUnlocked` helper.

#### `WBP_MissionHUD`
- Intel bar = `IntelScore / IntelThreshold` from `AVHGameState`.
- Reveal status text from `MissionPhase`.
- `Return to Hub` button -> `AVHPlayerController::ServerReturnToHub`.

## E) Multiplayer test checklist (2 clients PIE)
1. In editor, set **Play > Number of Players = 2**, Net Mode = **Play As Listen Server**.
2. Start PIE on `L_MainMenu`.
3. Host window clicks `Create Character`, confirms role/cosmetics, clicks `Host LAN`.
4. Client window clicks `Create Character`, confirms role/cosmetics, clicks `Join LAN`.
5. Verify in `L_BaseHub`:
   - both players visible,
   - cosmetics replicated,
   - per-player currency visible,
   - shared base level visible.
6. Host clicks `Start Mission`; verify both travel to `L_Mission01`.
7. Collect 3 Intel pickups; verify pickups disappear on both clients and shared IntelScore increases.
8. Verify monster transitions to revealable/hunt and starts chasing nearest player.
9. Kill monster; verify **team reward** currency granted to all players.
10. Click `Return to Hub`; verify server travels everyone back to `L_BaseHub` with updated currency.
