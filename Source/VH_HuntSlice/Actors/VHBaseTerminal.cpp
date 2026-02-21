#include "Actors/VHBaseTerminal.h"
#include "Game/VHGameState.h"
#include "Systems/VHProgressionSubsystem.h"

void AVHBaseTerminal::ServerInteract(AVHPlayerCharacter* Interactor)
{
    if (AVHGameState* GS = GetWorld()->GetGameState<AVHGameState>())
    {
        if (GS->TryUpgradeBase())
        {
            if (UVHProgressionSubsystem* Progression = GetGameInstance()->GetSubsystem<UVHProgressionSubsystem>())
            {
                Progression->SaveProgressionFromState(GS);
            }
        }
    }
}
