#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VHUIBlueprintLibrary.generated.h"

class UMonsterDefinition;

UCLASS()
class VHPHASMASLICE_API UVHUIBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category="VH|Codex")
    static bool IsMonsterUnlocked(const UMonsterDefinition* Definition, int32 BaseLevel);

    UFUNCTION(BlueprintPure, Category="VH|Codex")
    static int32 GetUpgradeCost(int32 BaseLevel) { return 100 * FMath::Max(1, BaseLevel); }
};
