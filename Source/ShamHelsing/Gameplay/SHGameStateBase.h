#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Systems/SHCoreTypes.h"
#include "SHGameStateBase.generated.h"

UCLASS()
class SHAMHELSING_API ASHGameStateBase : public AGameStateBase
{
    GENERATED_BODY()

public:
    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 TeamIntelCount = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    FName CurrentMonsterId = TEXT("Ghoul");

    UPROPERTY(Replicated, BlueprintReadOnly)
    EMissionPhase MissionPhase = EMissionPhase::Lobby;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 BaseLevel = 1;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 TeamCurrency = 0;

    UFUNCTION(BlueprintCallable)
    void AddIntel();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
