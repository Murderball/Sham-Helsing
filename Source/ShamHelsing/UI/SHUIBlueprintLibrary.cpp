#include "UI/SHUIBlueprintLibrary.h"
#include "Gameplay/SHGameStateBase.h"
#include "Gameplay/SHPlayerState.h"

FString USHUIBlueprintLibrary::BuildHubSummary(const ASHGameStateBase* GameState)
{
    if (!GameState)
    {
        return TEXT("No GameState");
    }

    return FString::Printf(TEXT("Base Lv.%d | Currency %d | Intel %d"), GameState->BaseLevel, GameState->TeamCurrency, GameState->TeamIntelCount);
}

FString USHUIBlueprintLibrary::BuildRoleDescription(const ASHPlayerState* PlayerState)
{
    if (!PlayerState) return TEXT("No role selected");

    switch (PlayerState->Role)
    {
    case EPlayerRole::MonsterHunter:
        return TEXT("Monster Hunter: 30% bonus damage against monsters.");
    case EPlayerRole::Investigator:
        return TEXT("Investigator: 50% faster intel scans and extended intel reveal range.");
    case EPlayerRole::Support:
        return TEXT("Support: Deploys a small restorative aura station for allies.");
    default:
        return TEXT("Unknown role.");
    }
}
