#include "Gameplay/SHPlayerCharacter.h"
#include "Gameplay/SHIntelActor.h"
#include "Gameplay/SHPlayerState.h"
#include "Systems/SHCoreTypes.h"

ASHPlayerCharacter::ASHPlayerCharacter()
{
    bReplicates = true;
}

void ASHPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

float ASHPlayerCharacter::GetDamageMultiplierForRole() const
{
    const ASHPlayerState* PS = GetPlayerState<ASHPlayerState>();
    if (!PS) return 1.f;

    if (PS->Role == EPlayerRole::MonsterHunter)
    {
        return 1.3f;
    }
    return 1.f;
}

void ASHPlayerCharacter::Interact()
{
    FVector Start;
    FRotator Rot;
    GetController()->GetPlayerViewPoint(Start, Rot);
    const FVector End = Start + (Rot.Vector() * 500.f);

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
    {
        if (ASHIntelActor* Intel = Cast<ASHIntelActor>(Hit.GetActor()))
        {
            ServerTryCollectIntel(Intel);
        }
    }
}

void ASHPlayerCharacter::ServerTryCollectIntel_Implementation(ASHIntelActor* IntelActor)
{
    if (IntelActor)
    {
        IntelActor->ServerScanIntel(this);
    }
}
