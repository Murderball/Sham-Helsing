# Blueprint Stub Setup (UE 5.7)

Create the following assets in-editor to complete the vertical slice wiring:

- `BP_FirstPersonCharacter` (child of `AVHPlayerCharacter`)
- `W_MainMenu` (Host/Join/Quit buttons -> `UVHSessionSubsystem`)
- `W_CreateCharacter` (6 presets + name; calls `AVHPlayerState::ServerSetAppearanceAndName`)
- `W_BaseHubHUD` (currency/base level/role + start hunt)
- `W_HuntHUD` (HP + IntelScore + objective)
- `W_InteractPrompt` (context use prompt)

Maps:
- `Map_MainMenu` -> `AVHMainMenuGameMode`
- `Map_BaseHub` -> `AVHBaseHubGameMode`, place `AVHBaseTerminal`
- `Map_Hunt01` -> `AVHHuntGameMode`, place clues and `AVHBanishAltar`

Clues:
- Place one each: `AVHClueResidue`, `AVHClueSigil`, `AVHClueWhisperRecorder`.

Data Assets:
- Create 3 `UVHMonsterTypeDataAsset` entries for level gates and assign to `AVHHuntGameMode::MonsterTypes`.
