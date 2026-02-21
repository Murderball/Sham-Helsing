#pragma once

#include "CoreMinimal.h"
#include "Core/VHTypes.h"
#include "GameFramework/PlayerState.h"
#include "VHPlayerState.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHPlayerState : public APlayerState
{
    GENERATED_BODY()
public:
    AVHPlayerState();

    UPROPERTY(Replicated, BlueprintReadOnly)
    FString VHPlayerName = TEXT("Hunter");

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 AppearancePresetId = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    EVHRole RoleEnum = EVHRole::MonsterHunter;

    UPROPERTY(Replicated, BlueprintReadOnly)
    float HP = 100.f;

    UPROPERTY(Replicated, BlueprintReadOnly)
    bool bDowned = false;

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerSetAppearanceAndName(int32 PresetId, const FString& NewName);

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerSetRole(EVHRole NewRole);

    UFUNCTION(BlueprintPure)
    float GetDamageMultiplier() const;

    UFUNCTION(BlueprintPure)
    float GetSupportMultiplier() const;

    UFUNCTION(BlueprintPure)
    float GetIntelRangeMultiplier() const;

    UFUNCTION(BlueprintPure)
    float GetTrapSlowMultiplier() const;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
