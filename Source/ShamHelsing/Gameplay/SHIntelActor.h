#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SHIntelActor.generated.h"

UCLASS()
class SHAMHELSING_API ASHIntelActor : public AActor
{
    GENERATED_BODY()

public:
    ASHIntelActor();

    UPROPERTY(ReplicatedUsing=OnRep_Collected, BlueprintReadOnly)
    bool bCollected = false;

    UFUNCTION(Server, Reliable)
    void ServerScanIntel(ACharacter* Scanner);

protected:
    UFUNCTION()
    void OnRep_Collected();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
