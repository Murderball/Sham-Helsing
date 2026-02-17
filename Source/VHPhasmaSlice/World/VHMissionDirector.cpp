#include "World/VHMissionDirector.h"

#include "AI/VHMonsterBase.h"
#include "GameModes/VHGameState.h"

AVHMissionDirector::AVHMissionDirector()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AVHMissionDirector::BeginPlay()
{
    Super::BeginPlay();
}

void AVHMissionDirector::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!HasAuthority() || bRevealTriggered)
    {
        return;
    }

    AVHGameState* GS = GetWorld()->GetGameState<AVHGameState>();
    if (!GS || !MissionMonster)
    {
        return;
    }

    if (GS->MissionPhase == EVHMissionPhase::MonsterRevealable)
    {
        bRevealTriggered = true;
        GS->SetMissionPhase(EVHMissionPhase::MonsterHunt);
        MissionMonster->SetRevealable(true);
    }
}
