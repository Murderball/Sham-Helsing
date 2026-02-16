#include "Gameplay/SHPlayerState.h"
#include "Net/UnrealNetwork.h"

ASHPlayerState::ASHPlayerState()
{
    bReplicates = true;
}

void ASHPlayerState::ServerSetRole_Implementation(EPlayerRole NewRole)
{
    Role = NewRole;
}

void ASHPlayerState::ServerSetPreset_Implementation(int32 NewPresetId)
{
    PresetId = FMath::Clamp(NewPresetId, 0, 5);
    OnRep_PresetId();
}

void ASHPlayerState::OnRep_PresetId()
{
}

void ASHPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ASHPlayerState, Role);
    DOREPLIFETIME(ASHPlayerState, PresetId);
    DOREPLIFETIME(ASHPlayerState, Currency);
}
