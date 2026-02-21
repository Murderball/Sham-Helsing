#include "Actors/VHBanishAltar.h"
#include "Game/VHHuntGameMode.h"
#include "Game/VHGameState.h"

void AVHBanishAltar::ServerInteract(AVHPlayerCharacter* Interactor)
{
    if (AVHGameState* GS = GetWorld()->GetGameState<AVHGameState>())
    {
        if (GS->IntelScore >= 3)
        {
            if (AVHHuntGameMode* GM = Cast<AVHHuntGameMode>(GetWorld()->GetAuthGameMode()))
            {
                GM->EvaluateHuntEnd(true);
            }
        }
    }
}
