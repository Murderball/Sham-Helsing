#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VHMissionDirector.generated.h"

class AVHMonsterBase;
class AVHGameState;

UCLASS()
class VHPHASMASLICE_API AVHMissionDirector : public AActor
{
    GENERATED_BODY()

public:
    AVHMissionDirector();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
    AVHMonsterBase* MissionMonster;

    bool bRevealTriggered = false;
};
