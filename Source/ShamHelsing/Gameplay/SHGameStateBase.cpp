#include "Gameplay/SHGameStateBase.h"
#include "Net/UnrealNetwork.h"

void ASHGameStateBase::AddIntel()
{
    if (HasAuthority())
    {
        TeamIntelCount++;
    }
}

void ASHGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ASHGameStateBase, TeamIntelCount);
    DOREPLIFETIME(ASHGameStateBase, CurrentMonsterId);
    DOREPLIFETIME(ASHGameStateBase, MissionPhase);
    DOREPLIFETIME(ASHGameStateBase, BaseLevel);
    DOREPLIFETIME(ASHGameStateBase, TeamCurrency);
}
