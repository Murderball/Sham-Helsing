#include "Game/VHGameModeBase.h"
#include "Game/VHGameState.h"
#include "Player/VHPlayerState.h"
#include "Systems/VHProgressionSubsystem.h"

AVHGameModeBase::AVHGameModeBase()
{
    GameStateClass = AVHGameState::StaticClass();
    PlayerStateClass = AVHPlayerState::StaticClass();
}

void AVHGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        if (UVHProgressionSubsystem* Progression = GetGameInstance()->GetSubsystem<UVHProgressionSubsystem>())
        {
            Progression->LoadProgression();
            Progression->ApplyToGameState(GetGameState<AVHGameState>());
        }
    }
}
