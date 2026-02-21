#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VHMonsterCharacter.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHMonsterCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    AVHMonsterCharacter();
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable)
    void ApplyDamage(float Amount);

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
    float HP = 150.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackDamage = 15.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ChaseRange = 2000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackRange = 150.f;

    float AttackCooldown = 0.f;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
