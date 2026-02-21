#include "Game/VHBaseHubGameMode.h"
#include "GameFramework/GameStateBase.h"

void AVHBaseHubGameMode::ServerStartHunt()
{
    if (HasAuthority())
    {
        GetWorld()->ServerTravel(TEXT("/Game/VH/Maps/Map_Hunt01?listen"));
    }
}
