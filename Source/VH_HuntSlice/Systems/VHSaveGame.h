#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VHSaveGame.generated.h"

UCLASS()
class VH_HUNTSLICE_API UVHSaveGame : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    int32 BaseLevel = 1;

    UPROPERTY(BlueprintReadWrite)
    int32 Currency = 0;

    UPROPERTY(BlueprintReadWrite)
    TArray<FName> UnlockedMonsters;

    UPROPERTY(BlueprintReadWrite)
    TMap<FString, int32> PlayerAppearanceByNetId;
};
