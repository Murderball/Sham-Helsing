#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Core/VHTypes.h"
#include "RoleDefinition.generated.h"

UCLASS(BlueprintType)
class VHPHASMASLICE_API URoleDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    EVHRoleType RoleType = EVHRoleType::MonsterHunter;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FRoleStats Stats;
};
