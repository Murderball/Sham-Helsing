#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VHPlayerController.generated.h"

UCLASS()
class VHPHASMASLICE_API AVHPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerTryUpgradeBase();

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerStartMission();

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerReturnToHub();
};
