#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "VHGameState.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHGameState : public AGameStateBase
{
    GENERATED_BODY()
public:
    AVHGameState();

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 BaseLevel = 1;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 Currency = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    TArray<FName> UnlockedMonsters;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 IntelScore = 0;

    UFUNCTION(BlueprintCallable)
    void AddIntel(int32 Amount);

    UFUNCTION(BlueprintCallable)
    bool TryUpgradeBase();

    UFUNCTION(BlueprintCallable)
    void AddCurrency(int32 Amount);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
