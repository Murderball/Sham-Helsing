#include "Gameplay/SHIntelActor.h"
#include "Gameplay/SHGameStateBase.h"
#include "Net/UnrealNetwork.h"

ASHIntelActor::ASHIntelActor()
{
    bReplicates = true;
    SetReplicateMovement(false);
}

void ASHIntelActor::ServerScanIntel_Implementation(ACharacter* Scanner)
{
    if (bCollected) return;

    bCollected = true;
    OnRep_Collected();

    if (ASHGameStateBase* GS = GetWorld()->GetGameState<ASHGameStateBase>())
    {
        GS->AddIntel();
    }
}

void ASHIntelActor::OnRep_Collected()
{
    SetActorHiddenInGame(bCollected);
    SetActorEnableCollision(!bCollected);
}

void ASHIntelActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ASHIntelActor, bCollected);
}
