#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SHUIBlueprintLibrary.generated.h"

class ASHGameStateBase;
class ASHPlayerState;

UCLASS()
class SHAMHELSING_API USHUIBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category="UI")
    static FString BuildHubSummary(const ASHGameStateBase* GameState);

    UFUNCTION(BlueprintPure, Category="UI")
    static FString BuildRoleDescription(const ASHPlayerState* PlayerState);
};
