#include "GameModes/VHGameState.h"

#include "Net/UnrealNetwork.h"
#include "Player/VHPlayerState.h"

AVHGameState::AVHGameState()
{
    bReplicates = true;
}

void AVHGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AVHGameState, BaseLevel);
    DOREPLIFETIME(AVHGameState, IntelScore);
    DOREPLIFETIME(AVHGameState, MissionPhase);
}

void AVHGameState::AddIntelScore(float Amount)
{
    if (!HasAuthority())
    {
        return;
    }

    IntelScore += Amount;
    if (IntelScore >= IntelThreshold && MissionPhase == EVHMissionPhase::GatheringIntel)
    {
        MissionPhase = EVHMissionPhase::MonsterRevealable;
    }
    OnRep_SharedState();
}

bool AVHGameState::TryUpgradeBase(AVHPlayerState* RequestingPlayer)
{
    if (!HasAuthority() || !RequestingPlayer)
    {
        return false;
    }

    const int32 UpgradeCost = 100 * BaseLevel;
    if (RequestingPlayer->GetCurrency() < UpgradeCost)
    {
        return false;
    }

    RequestingPlayer->AddCurrency(-UpgradeCost);
    BaseLevel++;
    OnRep_SharedState();
    return true;
}

void AVHGameState::MarkMissionCompleted()
{
    if (HasAuthority())
    {
        MissionPhase = EVHMissionPhase::Completed;
        OnRep_SharedState();
    }
}


void AVHGameState::SetMissionPhase(EVHMissionPhase NewPhase)
{
    if (HasAuthority())
    {
        MissionPhase = NewPhase;
        OnRep_SharedState();
    }
}

void AVHGameState::OnRep_SharedState()
{
    OnSharedStateChanged.Broadcast();
}
