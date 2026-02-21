#include "Player/VHPlayerState.h"
#include "Net/UnrealNetwork.h"

AVHPlayerState::AVHPlayerState()
{
    bReplicates = true;
}

void AVHPlayerState::ServerSetAppearanceAndName_Implementation(const int32 PresetId, const FString& NewName)
{
    AppearancePresetId = PresetId;
    VHPlayerName = NewName;
    SetPlayerName(NewName);
}

void AVHPlayerState::ServerSetRole_Implementation(const EVHRole NewRole)
{
    RoleEnum = NewRole;
}


float AVHPlayerState::GetDamageMultiplier() const
{
    return RoleEnum == EVHRole::MonsterHunter ? 1.25f : 1.0f;
}

float AVHPlayerState::GetSupportMultiplier() const
{
    return RoleEnum == EVHRole::Support ? 1.25f : 1.0f;
}

float AVHPlayerState::GetIntelRangeMultiplier() const
{
    return RoleEnum == EVHRole::Occultist ? 1.25f : 1.0f;
}

float AVHPlayerState::GetTrapSlowMultiplier() const
{
    return RoleEnum == EVHRole::Trapper ? 1.5f : 1.0f;
}

void AVHPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AVHPlayerState, VHPlayerName);
    DOREPLIFETIME(AVHPlayerState, AppearancePresetId);
    DOREPLIFETIME(AVHPlayerState, RoleEnum);
    DOREPLIFETIME(AVHPlayerState, HP);
    DOREPLIFETIME(AVHPlayerState, bDowned);
}
