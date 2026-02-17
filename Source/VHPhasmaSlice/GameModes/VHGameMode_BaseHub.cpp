#include "GameModes/VHGameMode_BaseHub.h"

#include "GameModes/VHGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/VHCharacter.h"
#include "Player/VHPlayerState.h"
#include "Player/VHPlayerController.h"

AVHGameMode_BaseHub::AVHGameMode_BaseHub()
{
    GameStateClass = AVHGameState::StaticClass();
    PlayerStateClass = AVHPlayerState::StaticClass();
    DefaultPawnClass = AVHCharacter::StaticClass();
    PlayerControllerClass = AVHPlayerController::StaticClass();
    bUseSeamlessTravel = false;
}

void AVHGameMode_BaseHub::StartMissionTravel()
{
    if (HasAuthority())
    {
        UGameplayStatics::OpenLevel(this, FName("L_Mission01"), true, TEXT("listen"));
    }
}
