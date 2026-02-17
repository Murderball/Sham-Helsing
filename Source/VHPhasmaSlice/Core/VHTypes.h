#pragma once

#include "CoreMinimal.h"
#include "VHTypes.generated.h"

UENUM(BlueprintType)
enum class EVHRoleType : uint8
{
    MonsterHunter UMETA(DisplayName="Monster Hunter"),
    Support UMETA(DisplayName="Support"),
    Analyst UMETA(DisplayName="Analyst")
};

UENUM(BlueprintType)
enum class EVHBodyPreset : uint8
{
    HunterA,
    HunterB,
    HunterC
};

UENUM(BlueprintType)
enum class EVHHeadPreset : uint8
{
    HeadA,
    HeadB,
    HeadC
};

UENUM(BlueprintType)
enum class EVHOutfitPreset : uint8
{
    OutfitA,
    OutfitB,
    OutfitC
};

UENUM(BlueprintType)
enum class EVHMissionPhase : uint8
{
    GatheringIntel,
    MonsterRevealable,
    MonsterHunt,
    Completed
};

USTRUCT(BlueprintType)
struct FRoleStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMultiplier = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float IntelMultiplier = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SupportPower = 0.f;
};

USTRUCT(BlueprintType)
struct FCharacterCosmetics
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EVHBodyPreset BodyPreset = EVHBodyPreset::HunterA;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EVHHeadPreset HeadPreset = EVHHeadPreset::HeadA;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EVHOutfitPreset OutfitPreset = EVHOutfitPreset::OutfitA;
};
