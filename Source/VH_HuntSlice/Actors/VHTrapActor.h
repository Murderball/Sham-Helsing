#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VHTrapActor.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHTrapActor : public AActor
{
    GENERATED_BODY()
public:
    AVHTrapActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SlowMultiplier = 0.5f;
};
