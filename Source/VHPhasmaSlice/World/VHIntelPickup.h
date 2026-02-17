#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VHIntelPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class VHPHASMASLICE_API AVHIntelPickup : public AActor
{
    GENERATED_BODY()

public:
    AVHIntelPickup();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY(VisibleAnywhere)
    USphereComponent* Sphere;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY(ReplicatedUsing=OnRep_Consumed)
    bool bConsumed = false;

    UPROPERTY(EditDefaultsOnly)
    float BaseIntelValue = 1.f;

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnRep_Consumed();
};
