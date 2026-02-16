#include "Gameplay/HuntGameMode.h"
#include "Gameplay/SHGameStateBase.h"
#include "Gameplay/SHMonsterCharacter.h"

void AHuntGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (!HasAuthority() || !MonsterClass) return;

    SpawnedMonster = GetWorld()->SpawnActor<ASHMonsterCharacter>(MonsterClass, FVector(0, 0, 150), FRotator::ZeroRotator);
    if (ASHGameStateBase* GS = GetGameState<ASHGameStateBase>())
    {
        const float IntelScale = FMath::Clamp(1.f - (0.1f * GS->TeamIntelCount), 0.3f, 1.f);
        if (SpawnedMonster)
        {
            SpawnedMonster->ApplyIntelHealthModifier(IntelScale);
        }
    }
}

void AHuntGameMode::CompleteMission(bool bMonsterDefeated)
{
    ASHGameStateBase* GS = GetGameState<ASHGameStateBase>();
    if (!GS) return;

    const int32 Reward = 50 + (GS->TeamIntelCount * 10) + (bMonsterDefeated ? 50 : 0);
    GS->TeamCurrency += Reward;
    GS->MissionPhase = EMissionPhase::Success;

    GetWorld()->ServerTravel(TEXT("/Game/Maps/Map_Hub?listen"), true);
}
