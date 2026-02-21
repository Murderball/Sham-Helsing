#include "Systems/VHProgressionSubsystem.h"
#include "Game/VHGameState.h"
#include "Kismet/GameplayStatics.h"

void UVHProgressionSubsystem::LoadProgression()
{
    if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
    {
        CachedSave = Cast<UVHSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
    }

    if (!CachedSave)
    {
        CachedSave = Cast<UVHSaveGame>(UGameplayStatics::CreateSaveGameObject(UVHSaveGame::StaticClass()));
        CachedSave->UnlockedMonsters = {FName(TEXT("Ghoul"))};
    }
}

void UVHProgressionSubsystem::SaveProgressionFromState(AVHGameState* GS)
{
    if (!GS)
    {
        return;
    }
    if (!CachedSave)
    {
        LoadProgression();
    }

    CachedSave->BaseLevel = GS->BaseLevel;
    CachedSave->Currency = GS->Currency;
    CachedSave->UnlockedMonsters = GS->UnlockedMonsters;
    UGameplayStatics::SaveGameToSlot(CachedSave, SlotName, 0);
}

void UVHProgressionSubsystem::ApplyToGameState(AVHGameState* GS) const
{
    if (!GS || !CachedSave)
    {
        return;
    }

    GS->BaseLevel = CachedSave->BaseLevel;
    GS->Currency = CachedSave->Currency;
    GS->UnlockedMonsters = CachedSave->UnlockedMonsters;
}

void UVHProgressionSubsystem::SavePlayerAppearance(const FString& PlayerKey, int32 PresetId)
{
    if (!CachedSave)
    {
        LoadProgression();
    }

    CachedSave->PlayerAppearanceByNetId.FindOrAdd(PlayerKey) = PresetId;
    UGameplayStatics::SaveGameToSlot(CachedSave, SlotName, 0);
}

int32 UVHProgressionSubsystem::LoadPlayerAppearance(const FString& PlayerKey) const
{
    if (!CachedSave)
    {
        return 0;
    }

    if (const int32* Found = CachedSave->PlayerAppearanceByNetId.Find(PlayerKey))
    {
        return *Found;
    }
    return 0;
}
