#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SHCoreTypes.h"
#include "SHProgressionLibrary.generated.h"

UCLASS()
class SHAMHELSING_API USHProgressionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Progression")
    static TArray<FMonsterData> BuildMonsterList();

    UFUNCTION(BlueprintCallable, Category="Progression")
    static TArray<FName> RecomputeUnlockedMonsters(int32 BaseLevel);

    UFUNCTION(BlueprintPure, Category="Progression")
    static int32 GetUpgradeCost(int32 CurrentBaseLevel) { return 100 * CurrentBaseLevel; }
};
