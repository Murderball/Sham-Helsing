#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SHMonsterCharacter.generated.h"

UCLASS()
class SHAMHELSING_API ASHMonsterCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASHMonsterCharacter();

    UPROPERTY(Replicated, BlueprintReadOnly)
    float MaxHP = 200.f;

    UPROPERTY(Replicated, BlueprintReadOnly)
    float CurrentHP = 200.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float MeleeDamage = 15.f;

    UFUNCTION(BlueprintCallable)
    void ApplyIntelHealthModifier(float Scale);

    UFUNCTION(BlueprintCallable)
    void ReceiveDamage(float Amount);

    virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
