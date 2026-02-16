#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SHPlayerCharacter.generated.h"

class ASHIntelActor;

UCLASS()
class SHAMHELSING_API ASHPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASHPlayerCharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseDamage = 20.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseScanDuration = 2.0f;

    UFUNCTION(BlueprintCallable)
    void Interact();

    UFUNCTION(Server, Reliable)
    void ServerTryCollectIntel(ASHIntelActor* IntelActor);

    UFUNCTION(BlueprintPure)
    float GetDamageMultiplierForRole() const;

protected:
    virtual void BeginPlay() override;
};
