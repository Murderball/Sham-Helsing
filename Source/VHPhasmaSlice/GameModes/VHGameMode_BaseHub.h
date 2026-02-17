#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VHGameMode_BaseHub.generated.h"

UCLASS()
class VHPHASMASLICE_API AVHGameMode_BaseHub : public AGameModeBase
{
    GENERATED_BODY()

public:
    AVHGameMode_BaseHub();

    UFUNCTION(BlueprintCallable)
    void StartMissionTravel();
};
