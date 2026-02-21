#include "Player/VHPlayerCharacter.h"
#include "Actors/VHInteractable.h"
#include "Actors/VHTrapActor.h"
#include "Monsters/VHMonsterCharacter.h"
#include "Player/VHPlayerState.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"

AVHPlayerCharacter::AVHPlayerCharacter()
{
    bReplicates = true;
}

void AVHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AVHPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AVHPlayerCharacter::MoveRight);
}

void AVHPlayerCharacter::MoveForward(const float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void AVHPlayerCharacter::MoveRight(const float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void AVHPlayerCharacter::ServerInteract_Implementation(AVHInteractable* Target)
{
    if (Target)
    {
        Target->ServerInteract(this);
    }
}

void AVHPlayerCharacter::ServerPlaceTrap_Implementation()
{
    const AVHPlayerState* VPS = GetPlayerState<AVHPlayerState>();
    if (!VPS || VPS->RoleEnum != EVHRole::Trapper)
    {
        return;
    }

    FActorSpawnParameters Params;
    Params.Owner = this;
    if (AVHTrapActor* Trap = GetWorld()->SpawnActor<AVHTrapActor>(AVHTrapActor::StaticClass(), GetActorLocation() + GetActorForwardVector() * 100.f, FRotator::ZeroRotator, Params))
    {
        Trap->SlowMultiplier *= VPS->GetTrapSlowMultiplier();
    }
}

void AVHPlayerCharacter::ServerPrimaryFire_Implementation()
{
    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    const FVector Start = GetActorLocation() + FVector(0, 0, 50.f);
    const FVector End = Start + GetControlRotation().Vector() * 1500.f;

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
    {
        if (AVHMonsterCharacter* Monster = Cast<AVHMonsterCharacter>(Hit.GetActor()))
        {
            float Damage = 20.f;
            if (const AVHPlayerState* VPS = GetPlayerState<AVHPlayerState>(); VPS && VPS->RoleEnum == EVHRole::MonsterHunter)
            {
                Damage *= VPS->GetDamageMultiplier();
            }
            Monster->ApplyDamage(Damage);
        }
    }
}
