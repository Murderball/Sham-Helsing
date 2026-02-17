#include "Player/VHPlayerState.h"

#include "Net/UnrealNetwork.h"

AVHPlayerState::AVHPlayerState()
{
    bReplicates = true;
}

void AVHPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AVHPlayerState, Currency);
    DOREPLIFETIME(AVHPlayerState, RoleType);
    DOREPLIFETIME(AVHPlayerState, Cosmetics);
    DOREPLIFETIME(AVHPlayerState, RoleStats);
}

void AVHPlayerState::ServerSetRoleAndCosmetics_Implementation(EVHRoleType InRole, const FCharacterCosmetics& InCosmetics)
{
    RoleType = InRole;
    Cosmetics = InCosmetics;
    RoleStats = GetDefaultStatsForRole(InRole);
    OnRep_PlayerData();
}

void AVHPlayerState::AddCurrency(int32 Amount)
{
    if (HasAuthority())
    {
        Currency = FMath::Max(0, Currency + Amount);
        OnRep_PlayerData();
    }
}

void AVHPlayerState::OnRep_PlayerData()
{
    OnPlayerDataChanged.Broadcast();
}

FRoleStats AVHPlayerState::GetDefaultStatsForRole(EVHRoleType InRole) const
{
    FRoleStats Stats;

    switch (InRole)
    {
    case EVHRoleType::MonsterHunter:
        Stats.DamageMultiplier = 1.35f;
        Stats.IntelMultiplier = 1.0f;
        Stats.SupportPower = 0.15f;
        break;
    case EVHRoleType::Support:
        Stats.DamageMultiplier = 1.0f;
        Stats.IntelMultiplier = 1.0f;
        Stats.SupportPower = 1.0f;
        break;
    case EVHRoleType::Analyst:
        Stats.DamageMultiplier = 0.9f;
        Stats.IntelMultiplier = 1.5f;
        Stats.SupportPower = 0.2f;
        break;
    default:
        break;
    }

    return Stats;
}
