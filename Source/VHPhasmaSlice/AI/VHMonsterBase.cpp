#include "AI/VHMonsterBase.h"

#include "Data/MonsterDefinition.h"
#include "GameModes/VHGameMode_Mission.h"
#include "GameModes/VHGameState.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AVHMonsterBase::AVHMonsterBase()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
}

void AVHMonsterBase::BeginPlay()
{
    Super::BeginPlay();

    if (Definition)
    {
        Health = Definition->MaxHealth;
    }
}

void AVHMonsterBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!HasAuthority() || !bRevealable)
    {
        return;
    }

    AActor* Target = FindNearestPlayer();
    if (!Target)
    {
        return;
    }

    const FVector ToTarget = Target->GetActorLocation() - GetActorLocation();
    const float Dist = ToTarget.Size();

    if (Dist > AttackRange)
    {
        const FVector Desired = ToTarget.GetSafeNormal();
        AddMovementInput(Desired, 1.0f);
        GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
    }
    else
    {
        UGameplayStatics::ApplyDamage(Target, ContactDamagePerSecond * DeltaSeconds, GetController(), this, nullptr);
    }
}

void AVHMonsterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AVHMonsterBase, Health);
    DOREPLIFETIME(AVHMonsterBase, bRevealable);
}

void AVHMonsterBase::SetRevealable(bool bInRevealable)
{
    if (HasAuthority())
    {
        bRevealable = bInRevealable;
        OnRep_Revealable();
    }
}

void AVHMonsterBase::ApplyDamage(float Damage, AActor* DamageCauser)
{
    if (!HasAuthority() || Damage <= 0.f)
    {
        return;
    }

    Health -= Damage;
    OnRep_Health();

    if (Health <= 0.f)
    {
        HandleDeath(DamageCauser);
    }
}

void AVHMonsterBase::OnRep_Health()
{
}

void AVHMonsterBase::OnRep_Revealable()
{
}

AActor* AVHMonsterBase::FindNearestPlayer() const
{
    AActor* Best = nullptr;
    float BestDistSq = FLT_MAX;

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (const APlayerController* PC = It->Get())
        {
            if (APawn* Pawn = PC->GetPawn())
            {
                const float DistSq = FVector::DistSquared(Pawn->GetActorLocation(), GetActorLocation());
                if (DistSq < BestDistSq)
                {
                    BestDistSq = DistSq;
                    Best = Pawn;
                }
            }
        }
    }

    return Best;
}

void AVHMonsterBase::HandleDeath(AActor* DamageCauser)
{
    AVHGameMode_Mission* MissionGM = GetWorld()->GetAuthGameMode<AVHGameMode_Mission>();
    if (MissionGM)
    {
        const int32 Reward = Definition ? Definition->RewardCurrency : 100;
        MissionGM->RewardTeamAndComplete(Reward);
    }

    Destroy();
}
