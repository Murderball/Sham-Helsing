#include "Systems/SHProgressionLibrary.h"

TArray<FMonsterData> USHProgressionLibrary::BuildMonsterList()
{
    TArray<FMonsterData> Out;

    FMonsterData Ghoul;
    Ghoul.MonsterId = TEXT("Ghoul");
    Ghoul.RequiredBaseLevel = 1;
    Ghoul.BaseHP = 140.f;
    Ghoul.BaseDamage = 10.f;
    Ghoul.WeaknessTag = TEXT("Fire");
    Out.Add(Ghoul);

    FMonsterData Wraith;
    Wraith.MonsterId = TEXT("Wraith");
    Wraith.RequiredBaseLevel = 2;
    Wraith.BaseHP = 190.f;
    Wraith.BaseDamage = 15.f;
    Wraith.WeaknessTag = TEXT("Silver");
    Out.Add(Wraith);

    FMonsterData Vampire;
    Vampire.MonsterId = TEXT("VampireSpawn");
    Vampire.RequiredBaseLevel = 3;
    Vampire.BaseHP = 260.f;
    Vampire.BaseDamage = 20.f;
    Vampire.WeaknessTag = TEXT("Holy");
    Out.Add(Vampire);

    return Out;
}

TArray<FName> USHProgressionLibrary::RecomputeUnlockedMonsters(const int32 BaseLevel)
{
    TArray<FName> Unlocked;
    for (const FMonsterData& Data : BuildMonsterList())
    {
        if (BaseLevel >= Data.RequiredBaseLevel)
        {
            Unlocked.Add(Data.MonsterId);
        }
    }
    return Unlocked;
}
