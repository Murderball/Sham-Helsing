#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SHCoreTypes.h"
#include "SG_PlayerProfile.generated.h"

UCLASS()
class SHAMHELSING_API USG_PlayerProfile : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PresetId = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPlayerRole LastRole = EPlayerRole::MonsterHunter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Currency = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UnlockedMonsters;
};
