#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VHGameModeBase.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
public:
    AVHGameModeBase();

protected:
    virtual void BeginPlay() override;
};
