#include "GameModes/VHGameMode_Mission.h"

#include "EngineUtils.h"
#include "GameModes/VHGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/VHCharacter.h"
#include "Player/VHPlayerState.h"
#include "Player/VHPlayerController.h"

AVHGameMode_Mission::AVHGameMode_Mission()
{
    GameStateClass = AVHGameState::StaticClass();
    PlayerStateClass = AVHPlayerState::StaticClass();
    DefaultPawnClass = AVHCharacter::StaticClass();
    PlayerControllerClass = AVHPlayerController::StaticClass();
}

void AVHGameMode_Mission::ReturnToHub()
{
    if (HasAuthority())
    {
        UGameplayStatics::OpenLevel(this, FName("L_BaseHub"), true, TEXT("listen"));
    }
}

void AVHGameMode_Mission::RewardTeamAndComplete(int32 RewardCurrency)
{
    if (!HasAuthority())
    {
        return;
    }

    for (APlayerState* PlayerState : GameState->PlayerArray)
    {
        if (AVHPlayerState* VHPS = Cast<AVHPlayerState>(PlayerState))
        {
            VHPS->AddCurrency(RewardCurrency);
        }
    }

    if (AVHGameState* VHGS = GetGameState<AVHGameState>())
    {
        VHGS->MarkMissionCompleted();
    }
}
