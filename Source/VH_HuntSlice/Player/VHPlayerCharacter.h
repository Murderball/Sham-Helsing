#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VHPlayerCharacter.generated.h"

class AVHInteractable;

UCLASS()
class VH_HUNTSLICE_API AVHPlayerCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    AVHPlayerCharacter();

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UFUNCTION(Server, Reliable)
    void ServerInteract(AVHInteractable* Target);

    UFUNCTION(Server, Reliable)
    void ServerPlaceTrap();

    UFUNCTION(Server, Reliable)
    void ServerPrimaryFire();

protected:
    void MoveForward(float Value);
    void MoveRight(float Value);
};
