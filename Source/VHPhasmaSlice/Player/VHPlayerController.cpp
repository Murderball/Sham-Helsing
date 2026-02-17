#include "Player/VHPlayerController.h"

#include "GameModes/VHGameMode_BaseHub.h"
#include "GameModes/VHGameMode_Mission.h"
#include "GameModes/VHGameState.h"
#include "Player/VHPlayerState.h"

void AVHPlayerController::ServerTryUpgradeBase_Implementation()
{
    AVHGameState* GS = GetWorld()->GetGameState<AVHGameState>();
    AVHPlayerState* PS = GetPlayerState<AVHPlayerState>();
    if (GS && PS)
    {
        GS->TryUpgradeBase(PS);
    }
}

void AVHPlayerController::ServerStartMission_Implementation()
{
    if (AVHGameMode_BaseHub* GM = GetWorld()->GetAuthGameMode<AVHGameMode_BaseHub>())
    {
        GM->StartMissionTravel();
    }
}

void AVHPlayerController::ServerReturnToHub_Implementation()
{
    if (AVHGameMode_Mission* GM = GetWorld()->GetAuthGameMode<AVHGameMode_Mission>())
    {
        GM->ReturnToHub();
    }
}
