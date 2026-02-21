#include "Game/VHHuntGameMode.h"
#include "Game/VHGameState.h"
#include "Monsters/VHMonsterCharacter.h"
#include "Systems/VHProgressionSubsystem.h"
#include "Player/VHPlayerState.h"
#include "Data/VHMonsterTypeDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

AVHHuntGameMode::AVHHuntGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AVHHuntGameMode::BeginPlay()
{
    Super::BeginPlay();
    RemainingTime = HuntTimeLimit;

    if (HasAuthority() && MonsterClass)
    {
        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        AVHMonsterCharacter* Monster = GetWorld()->SpawnActor<AVHMonsterCharacter>(MonsterClass, FVector(0, 0, 100), FRotator::ZeroRotator, Params);

        if (Monster)
        {
            const AVHGameState* GS = GetGameState<AVHGameState>();
            int32 BestReq = -1;
            UVHMonsterTypeDataAsset* Best = nullptr;
            for (UVHMonsterTypeDataAsset* Type : MonsterTypes)
            {
                if (Type && GS && Type->BaseLevelRequired <= GS->BaseLevel && Type->BaseLevelRequired > BestReq)
                {
                    BestReq = Type->BaseLevelRequired;
                    Best = Type;
                }
            }
            if (Best)
            {
                Monster->HP = Best->HP;
                Monster->AttackDamage = Best->Damage;
                Monster->GetCharacterMovement()->MaxWalkSpeed = Best->Speed;
            }
        }
    }
}

void AVHHuntGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!HasAuthority() || bResolved)
    {
        return;
    }

    RemainingTime -= DeltaSeconds;
    bool bAllDown = true;
    for (APlayerState* PS : GameState->PlayerArray)
    {
        if (const AVHPlayerState* VPS = Cast<AVHPlayerState>(PS))
        {
            if (!VPS->bDowned)
            {
                bAllDown = false;
                break;
            }
        }
    }

    if (RemainingTime <= 0.f || bAllDown)
    {
        EvaluateHuntEnd(false);
    }
}

void AVHHuntGameMode::EvaluateHuntEnd(const bool bWon)
{
    if (!HasAuthority() || bResolved)
    {
        return;
    }
    bResolved = true;

    AVHGameState* GS = GetGameState<AVHGameState>();
    if (GS)
    {
        GS->AddCurrency(bWon ? 150 : 50);
        if (UVHProgressionSubsystem* Progression = GetGameInstance()->GetSubsystem<UVHProgressionSubsystem>())
        {
            Progression->SaveProgressionFromState(GS);
        }
    }

    GetWorld()->ServerTravel(TEXT("/Game/VH/Maps/Map_BaseHub?listen"));
}
