#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterDefinition.generated.h"

UCLASS(BlueprintType)
class VHPHASMASLICE_API UMonsterDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName MonsterId = "Monster_Wraith";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 UnlockBaseLevel = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float MaxHealth = 150.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 RewardCurrency = 150;
};
