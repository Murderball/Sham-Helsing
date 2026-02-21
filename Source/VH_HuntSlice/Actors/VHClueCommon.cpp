#include "Actors/VHClueResidue.h"
#include "Actors/VHClueSigil.h"
#include "Actors/VHClueWhisperRecorder.h"
#include "Game/VHGameState.h"

static void ConsumeClue(AVHInteractable* Self)
{
    if (!Self || Self->HasAuthority() == false)
    {
        return;
    }

    if (AVHGameState* GS = Self->GetWorld()->GetGameState<AVHGameState>())
    {
        GS->AddIntel(1);
    }
    Self->SetActorHiddenInGame(true);
    Self->SetActorEnableCollision(false);
}

void AVHClueResidue::ServerInteract(AVHPlayerCharacter* Interactor)
{
    ConsumeClue(this);
}

void AVHClueSigil::ServerInteract(AVHPlayerCharacter* Interactor)
{
    ConsumeClue(this);
}

void AVHClueWhisperRecorder::ServerInteract(AVHPlayerCharacter* Interactor)
{
    ConsumeClue(this);
}
