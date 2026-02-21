#include "Actors/VHInteractable.h"
#include "Net/UnrealNetwork.h"

AVHInteractable::AVHInteractable()
{
    bReplicates = true;
}

void AVHInteractable::ServerInteract(AVHPlayerCharacter* Interactor)
{
}

void AVHInteractable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AVHInteractable, bConsumed);
}
