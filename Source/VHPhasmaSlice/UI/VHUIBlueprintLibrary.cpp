#include "UI/VHUIBlueprintLibrary.h"

#include "Data/MonsterDefinition.h"

bool UVHUIBlueprintLibrary::IsMonsterUnlocked(const UMonsterDefinition* Definition, int32 BaseLevel)
{
    return Definition && BaseLevel >= Definition->UnlockBaseLevel;
}
