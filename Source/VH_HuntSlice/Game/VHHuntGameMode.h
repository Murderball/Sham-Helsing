#pragma once

#include "CoreMinimal.h"
#include "Game/VHGameModeBase.h"
#include "VHHuntGameMode.generated.h"

class UVHMonsterTypeDataAsset;

UCLASS()
class VH_HUNTSLICE_API AVHHuntGameMode : public AVHGameModeBase
{
    GENERATED_BODY()
public:
    AVHHuntGameMode();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 IntelTarget = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float HuntTimeLimit = 300.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<class AVHMonsterCharacter> MonsterClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<UVHMonsterTypeDataAsset*> MonsterTypes;

    UFUNCTION(BlueprintCallable)
    void EvaluateHuntEnd(bool bWon);

private:
    float RemainingTime = 0.f;
    bool bResolved = false;
};
