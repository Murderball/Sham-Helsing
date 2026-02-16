#include "Gameplay/HubGameMode.h"
#include "Gameplay/SHGameStateBase.h"
#include "Systems/SHProgressionLibrary.h"

void AHubGameMode::ServerStartHunt(const FName MonsterId)
{
    if (UWorld* World = GetWorld())
    {
        if (ASHGameStateBase* GS = GetGameState<ASHGameStateBase>())
        {
            GS->CurrentMonsterId = MonsterId;
            GS->TeamIntelCount = 0;
            GS->MissionPhase = EMissionPhase::HuntInProgress;
        }
        World->ServerTravel(TEXT("/Game/Maps/Map_Hunt_01?listen"), true);
    }
}

bool AHubGameMode::ServerUpgradeBase()
{
    ASHGameStateBase* GS = GetGameState<ASHGameStateBase>();
    if (!GS) return false;

    const int32 Cost = USHProgressionLibrary::GetUpgradeCost(GS->BaseLevel);
    if (GS->TeamCurrency < Cost)
    {
        return false;
    }

    GS->TeamCurrency -= Cost;
    GS->BaseLevel += 1;
    return true;
}
