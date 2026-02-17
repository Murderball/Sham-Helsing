#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VHGameMode_Mission.generated.h"

UCLASS()
class VHPHASMASLICE_API AVHGameMode_Mission : public AGameModeBase
{
    GENERATED_BODY()

public:
    AVHGameMode_Mission();

    UFUNCTION(BlueprintCallable)
    void ReturnToHub();

    UFUNCTION(BlueprintCallable)
    void RewardTeamAndComplete(int32 RewardCurrency);
};
