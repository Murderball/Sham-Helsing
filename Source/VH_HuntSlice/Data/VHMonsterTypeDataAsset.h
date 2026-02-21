#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VHMonsterTypeDataAsset.generated.h"

UCLASS(BlueprintType)
class VH_HUNTSLICE_API UVHMonsterTypeDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName Name = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 BaseLevelRequired = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float HP = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Damage = 15.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Speed = 350.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FLinearColor VisualColor = FLinearColor::Red;
};
