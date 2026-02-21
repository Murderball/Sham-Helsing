#include "Monsters/VHMonsterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/VHPlayerCharacter.h"
#include "Player/VHPlayerState.h"
#include "Game/VHHuntGameMode.h"
#include "Net/UnrealNetwork.h"

AVHMonsterCharacter::AVHMonsterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    GetCharacterMovement()->MaxWalkSpeed = 320.f;
}

void AVHMonsterCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AVHMonsterCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!HasAuthority())
    {
        return;
    }

    AttackCooldown -= DeltaSeconds;

    APawn* BestPawn = nullptr;
    float BestDistSq = FLT_MAX;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (APawn* P = It->Get()->GetPawn())
        {
            const float DistSq = FVector::DistSquared(P->GetActorLocation(), GetActorLocation());
            if (DistSq < BestDistSq)
            {
                BestDistSq = DistSq;
                BestPawn = P;
            }
        }
    }

    if (!BestPawn || BestDistSq > FMath::Square(ChaseRange))
    {
        return;
    }

    const FVector Dir = (BestPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
    AddMovementInput(Dir, 1.f);

    if (BestDistSq <= FMath::Square(AttackRange) && AttackCooldown <= 0.f)
    {
        if (AVHPlayerState* PS = BestPawn->GetPlayerState<AVHPlayerState>())
        {
            PS->HP = FMath::Max(0.f, PS->HP - AttackDamage);
            PS->bDowned = PS->HP <= 0.f;
        }
        AttackCooldown = 1.2f;
    }
}

void AVHMonsterCharacter::ApplyDamage(const float Amount)
{
    if (!HasAuthority())
    {
        return;
    }

    HP -= Amount;
    if (HP <= 0.f)
    {
        if (AVHHuntGameMode* GM = Cast<AVHHuntGameMode>(UGameplayStatics::GetGameMode(this)))
        {
            GM->EvaluateHuntEnd(true);
        }
        Destroy();
    }
}

void AVHMonsterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AVHMonsterCharacter, HP);
}
