#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Core/VHTypes.h"
#include "VHCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UStaticMeshComponent;

UCLASS()
class VHPHASMASLICE_API AVHCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AVHCharacter();

    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable)
    void RequestApplyFromPlayerState();

protected:
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* FirstPersonCamera;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CosmeticProxy;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    UInputMappingContext* DefaultContext;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    UInputAction* IA_Move;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    UInputAction* IA_Look;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    UInputAction* IA_Jump;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    UInputAction* IA_Fire;

    UPROPERTY(ReplicatedUsing=OnRep_Cosmetics)
    FCharacterCosmetics RepCosmetics;

    UPROPERTY(Replicated)
    FRoleStats RepRoleStats;

    UPROPERTY(EditDefaultsOnly, Category="Combat")
    float BaseDamage = 30.f;

    UFUNCTION()
    void OnRep_Cosmetics();

    UFUNCTION(Server, Reliable)
    void ServerFire();

    void MoveInput(const FInputActionValue& Value);
    void LookInput(const FInputActionValue& Value);
    void FireInput();
    void ApplyCosmeticsVisuals();
};
