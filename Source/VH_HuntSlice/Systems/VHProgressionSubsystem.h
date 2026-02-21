#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Systems/VHSaveGame.h"
#include "VHProgressionSubsystem.generated.h"

class AVHGameState;

UCLASS()
class VH_HUNTSLICE_API UVHProgressionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void LoadProgression();

    UFUNCTION(BlueprintCallable)
    void SaveProgressionFromState(AVHGameState* GS);

    UFUNCTION(BlueprintCallable)
    void ApplyToGameState(AVHGameState* GS) const;

    UFUNCTION(BlueprintCallable)
    void SavePlayerAppearance(const FString& PlayerKey, int32 PresetId);

    UFUNCTION(BlueprintCallable)
    int32 LoadPlayerAppearance(const FString& PlayerKey) const;

private:
    UPROPERTY()
    UVHSaveGame* CachedSave = nullptr;

    FString SlotName = TEXT("VH_HuntSlice_Save");
};
