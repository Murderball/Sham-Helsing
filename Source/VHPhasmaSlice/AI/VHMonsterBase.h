#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VHMonsterBase.generated.h"

class UMonsterDefinition;

UCLASS()
class VHPHASMASLICE_API AVHMonsterBase : public ACharacter
{
    GENERATED_BODY()

public:
    AVHMonsterBase();

    virtual void Tick(float DeltaSeconds) override;
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable)
    void SetRevealable(bool bInRevealable);

    UFUNCTION(BlueprintCallable)
    void ApplyDamage(float Damage, AActor* DamageCauser);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UMonsterDefinition* Definition;

protected:
    UPROPERTY(ReplicatedUsing=OnRep_Health, BlueprintReadOnly)
    float Health = 100.f;

    UPROPERTY(ReplicatedUsing=OnRep_Revealable, BlueprintReadOnly)
    bool bRevealable = false;

    UPROPERTY(EditDefaultsOnly)
    float ChaseSpeed = 350.f;

    UPROPERTY(EditDefaultsOnly)
    float AttackRange = 150.f;

    UPROPERTY(EditDefaultsOnly)
    float ContactDamagePerSecond = 15.f;

    UFUNCTION()
    void OnRep_Health();

    UFUNCTION()
    void OnRep_Revealable();

    AActor* FindNearestPlayer() const;
    void HandleDeath(AActor* DamageCauser);
};
