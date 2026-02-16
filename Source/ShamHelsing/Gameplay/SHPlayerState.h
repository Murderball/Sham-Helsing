#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Systems/SHCoreTypes.h"
#include "SHPlayerState.generated.h"

UCLASS()
class SHAMHELSING_API ASHPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ASHPlayerState();

    UPROPERTY(Replicated, BlueprintReadOnly)
    EPlayerRole Role = EPlayerRole::MonsterHunter;

    UPROPERTY(ReplicatedUsing=OnRep_PresetId, BlueprintReadOnly)
    int32 PresetId = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 Currency = 0;

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerSetRole(EPlayerRole NewRole);

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerSetPreset(int32 NewPresetId);

protected:
    UFUNCTION()
    void OnRep_PresetId();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
