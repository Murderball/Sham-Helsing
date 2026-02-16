#include "Gameplay/SHMonsterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ASHMonsterCharacter::ASHMonsterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    SetReplicateMovement(true);
}

void ASHMonsterCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ASHMonsterCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!HasAuthority()) return;

    APawn* Closest = nullptr;
    float BestDist = TNumericLimits<float>::Max();

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (const APlayerController* PC = It->Get())
        {
            APawn* P = PC->GetPawn();
            if (!P) continue;
            const float Dist = FVector::DistSquared(P->GetActorLocation(), GetActorLocation());
            if (Dist < BestDist)
            {
                BestDist = Dist;
                Closest = P;
            }
        }
    }

    if (Closest)
    {
        const float Dist = FVector::Dist(Closest->GetActorLocation(), GetActorLocation());
        if (Dist > 150.f)
        {
            AddMovementInput((Closest->GetActorLocation() - GetActorLocation()).GetSafeNormal(), 1.f);
        }
        else
        {
            UGameplayStatics::ApplyDamage(Closest, MeleeDamage, nullptr, this, nullptr);
        }
    }
}

void ASHMonsterCharacter::ApplyIntelHealthModifier(float Scale)
{
    if (!HasAuthority()) return;
    MaxHP = FMath::Max(30.f, MaxHP * Scale);
    CurrentHP = MaxHP;
}

void ASHMonsterCharacter::ReceiveDamage(float Amount)
{
    if (!HasAuthority()) return;
    CurrentHP = FMath::Max(0.f, CurrentHP - Amount);
    if (CurrentHP <= 0.f)
    {
        Destroy();
    }
}

void ASHMonsterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ASHMonsterCharacter, MaxHP);
    DOREPLIFETIME(ASHMonsterCharacter, CurrentHP);
}
