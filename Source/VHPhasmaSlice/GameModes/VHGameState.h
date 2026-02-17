#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Core/VHTypes.h"
#include "VHGameState.generated.h"

class AVHPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVHSharedStateChanged);

UCLASS()
class VHPHASMASLICE_API AVHGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    AVHGameState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(BlueprintAssignable)
    FVHSharedStateChanged OnSharedStateChanged;

    UFUNCTION(BlueprintCallable)
    void AddIntelScore(float Amount);

    UFUNCTION(BlueprintCallable)
    bool TryUpgradeBase(AVHPlayerState* RequestingPlayer);

    UFUNCTION(BlueprintCallable)
    void MarkMissionCompleted();

    UFUNCTION(BlueprintCallable)
    void SetMissionPhase(EVHMissionPhase NewPhase);

    UFUNCTION(BlueprintPure)
    bool IsMonsterRevealable() const { return MissionPhase != EVHMissionPhase::GatheringIntel; }

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float IntelThreshold = 3.0f;

    UPROPERTY(ReplicatedUsing=OnRep_SharedState, BlueprintReadOnly)
    int32 BaseLevel = 1;

    UPROPERTY(ReplicatedUsing=OnRep_SharedState, BlueprintReadOnly)
    float IntelScore = 0.f;

    UPROPERTY(ReplicatedUsing=OnRep_SharedState, BlueprintReadOnly)
    EVHMissionPhase MissionPhase = EVHMissionPhase::GatheringIntel;

protected:
    UFUNCTION()
    void OnRep_SharedState();
};
