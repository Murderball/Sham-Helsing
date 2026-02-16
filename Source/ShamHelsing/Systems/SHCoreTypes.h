#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SHCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
    MonsterHunter UMETA(DisplayName = "Monster Hunter"),
    Investigator UMETA(DisplayName = "Investigator"),
    Support UMETA(DisplayName = "Support")
};

UENUM(BlueprintType)
enum class EMissionPhase : uint8
{
    Lobby,
    HuntInProgress,
    Success,
    Failed
};

USTRUCT(BlueprintType)
struct FMonsterData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName MonsterId = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 RequiredBaseLevel = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseHP = 100.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseDamage = 15.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FString WeaknessTag = TEXT("Holy");
};
