#include "World/VHIntelPickup.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Data/RoleDefinition.h"
#include "GameModes/VHGameState.h"
#include "Net/UnrealNetwork.h"
#include "Player/VHPlayerState.h"
#include "Player/VHCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVHIntelPickup::AVHIntelPickup()
{
    bReplicates = true;

    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    SetRootComponent(Sphere);
    Sphere->SetSphereRadius(75.f);
    Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AVHIntelPickup::OnOverlap);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        Mesh->SetStaticMesh(SphereMesh.Object);
    }
}

void AVHIntelPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AVHIntelPickup, bConsumed);
}

void AVHIntelPickup::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority() || bConsumed)
    {
        return;
    }

    AVHCharacter* VHChar = Cast<AVHCharacter>(OtherActor);
    if (!VHChar)
    {
        return;
    }

    bConsumed = true;

    float Multiplier = 1.f;
    if (const AVHPlayerState* VHPS = VHChar->GetPlayerState<AVHPlayerState>())
    {
        Multiplier = VHPS->GetRoleStats().IntelMultiplier;
    }

    if (AVHGameState* VHGS = GetWorld()->GetGameState<AVHGameState>())
    {
        VHGS->AddIntelScore(BaseIntelValue * Multiplier);
    }

    OnRep_Consumed();
}

void AVHIntelPickup::OnRep_Consumed()
{
    SetActorHiddenInGame(bConsumed);
    SetActorEnableCollision(!bConsumed);
    SetActorTickEnabled(!bConsumed);
}
