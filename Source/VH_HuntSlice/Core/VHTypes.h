#pragma once

#include "CoreMinimal.h"
#include "VHTypes.generated.h"

UENUM(BlueprintType)
enum class EVHRole : uint8
{
    MonsterHunter,
    Support,
    Occultist,
    Trapper
};

USTRUCT(BlueprintType)
struct FMonsterUnlockInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MonsterName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredBaseLevel = 1;
};
