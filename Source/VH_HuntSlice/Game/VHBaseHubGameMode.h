#pragma once

#include "Game/VHGameModeBase.h"
#include "VHBaseHubGameMode.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHBaseHubGameMode : public AVHGameModeBase
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void ServerStartHunt();
};
