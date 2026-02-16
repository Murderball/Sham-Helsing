#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HubGameMode.generated.h"

UCLASS()
class SHAMHELSING_API AHubGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void ServerStartHunt(const FName MonsterId);

    UFUNCTION(BlueprintCallable)
    bool ServerUpgradeBase();
};
