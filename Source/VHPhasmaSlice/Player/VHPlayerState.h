#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Core/VHTypes.h"
#include "VHPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVHPlayerStateChanged);

UCLASS()
class VHPHASMASLICE_API AVHPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    AVHPlayerState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(BlueprintAssignable)
    FVHPlayerStateChanged OnPlayerDataChanged;

    UFUNCTION(BlueprintPure)
    int32 GetCurrency() const { return Currency; }

    UFUNCTION(BlueprintPure)
    EVHRoleType GetRoleType() const { return RoleType; }

    UFUNCTION(BlueprintPure)
    const FCharacterCosmetics& GetCosmetics() const { return Cosmetics; }

    UFUNCTION(BlueprintPure)
    const FRoleStats& GetRoleStats() const { return RoleStats; }

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerSetRoleAndCosmetics(EVHRoleType InRole, const FCharacterCosmetics& InCosmetics);

    UFUNCTION(BlueprintCallable)
    void AddCurrency(int32 Amount);

protected:
    UPROPERTY(ReplicatedUsing=OnRep_PlayerData, BlueprintReadOnly)
    int32 Currency = 0;

    UPROPERTY(ReplicatedUsing=OnRep_PlayerData, BlueprintReadOnly)
    EVHRoleType RoleType = EVHRoleType::MonsterHunter;

    UPROPERTY(ReplicatedUsing=OnRep_PlayerData, BlueprintReadOnly)
    FCharacterCosmetics Cosmetics;

    UPROPERTY(ReplicatedUsing=OnRep_PlayerData, BlueprintReadOnly)
    FRoleStats RoleStats;

    UFUNCTION()
    void OnRep_PlayerData();

    FRoleStats GetDefaultStatsForRole(EVHRoleType InRole) const;
};
