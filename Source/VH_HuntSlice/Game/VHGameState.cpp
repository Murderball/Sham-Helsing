#include "Game/VHGameState.h"
#include "Net/UnrealNetwork.h"

AVHGameState::AVHGameState()
{
    bReplicates = true;
}

void AVHGameState::AddIntel(const int32 Amount)
{
    IntelScore += Amount;
}

bool AVHGameState::TryUpgradeBase()
{
    const int32 Cost = BaseLevel * 100;
    if (Currency < Cost)
    {
        return false;
    }

    Currency -= Cost;
    ++BaseLevel;
    if (BaseLevel >= 2 && !UnlockedMonsters.Contains(FName(TEXT("Wraith"))))
    {
        UnlockedMonsters.Add(FName(TEXT("Wraith")));
    }
    if (BaseLevel >= 3 && !UnlockedMonsters.Contains(FName(TEXT("Vampire"))))
    {
        UnlockedMonsters.Add(FName(TEXT("Vampire")));
    }
    return true;
}

void AVHGameState::AddCurrency(const int32 Amount)
{
    Currency += Amount;
}

void AVHGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AVHGameState, BaseLevel);
    DOREPLIFETIME(AVHGameState, Currency);
    DOREPLIFETIME(AVHGameState, UnlockedMonsters);
    DOREPLIFETIME(AVHGameState, IntelScore);
}
