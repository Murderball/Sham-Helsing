#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VHInteractable.generated.h"

class AVHPlayerCharacter;

UCLASS()
class VH_HUNTSLICE_API AVHInteractable : public AActor
{
    GENERATED_BODY()
public:
    AVHInteractable();

    UFUNCTION(BlueprintCallable)
    virtual void ServerInteract(AVHPlayerCharacter* Interactor);

protected:
    UPROPERTY(Replicated, BlueprintReadOnly)
    bool bConsumed = false;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
