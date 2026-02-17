#include "Player/VHCharacter.h"

#include "AI/VHMonsterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/VHPlayerState.h"
#include "UObject/ConstructorHelpers.h"

AVHCharacter::AVHCharacter()
{
    bReplicates = true;

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
    FirstPersonCamera->bUsePawnControlRotation = true;

    CosmeticProxy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CosmeticProxy"));
    CosmeticProxy->SetupAttachment(GetRootComponent());
    CosmeticProxy->SetRelativeScale3D(FVector(0.4f, 0.4f, 1.0f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        CosmeticProxy->SetStaticMesh(CubeMesh.Object);
    }
}

void AVHCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(Controller))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                if (DefaultContext)
                {
                    InputSubsystem->AddMappingContext(DefaultContext, 0);
                }
            }
        }
    }

    RequestApplyFromPlayerState();
}

void AVHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (!EIC)
    {
        return;
    }

    if (IA_Move)
    {
        EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AVHCharacter::MoveInput);
    }
    if (IA_Look)
    {
        EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AVHCharacter::LookInput);
    }
    if (IA_Jump)
    {
        EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
        EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
    }
    if (IA_Fire)
    {
        EIC->BindAction(IA_Fire, ETriggerEvent::Started, this, &AVHCharacter::FireInput);
    }
}

void AVHCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AVHCharacter, RepCosmetics);
    DOREPLIFETIME(AVHCharacter, RepRoleStats);
}

void AVHCharacter::RequestApplyFromPlayerState()
{
    if (AVHPlayerState* VHPS = GetPlayerState<AVHPlayerState>())
    {
        if (HasAuthority())
        {
            RepCosmetics = VHPS->GetCosmetics();
            RepRoleStats = VHPS->GetRoleStats();
            ApplyCosmeticsVisuals();
        }
    }
}

void AVHCharacter::OnRep_Cosmetics()
{
    ApplyCosmeticsVisuals();
}

void AVHCharacter::ServerFire_Implementation()
{
    if (!Controller)
    {
        return;
    }

    FVector EyeLocation;
    FRotator EyeRotation;
    Controller->GetPlayerViewPoint(EyeLocation, EyeRotation);

    const FVector End = EyeLocation + EyeRotation.Vector() * 3000.f;

    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(WeaponTrace), false, this);

    if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, End, ECC_Visibility, Params))
    {
        if (AVHMonsterBase* Monster = Cast<AVHMonsterBase>(Hit.GetActor()))
        {
            const float Damage = BaseDamage * FMath::Max(0.1f, RepRoleStats.DamageMultiplier);
            Monster->ApplyDamage(Damage, this);
        }
    }
}

void AVHCharacter::MoveInput(const FInputActionValue& Value)
{
    const FVector2D Move = Value.Get<FVector2D>();
    AddMovementInput(GetActorForwardVector(), Move.Y);
    AddMovementInput(GetActorRightVector(), Move.X);
}

void AVHCharacter::LookInput(const FInputActionValue& Value)
{
    const FVector2D Look = Value.Get<FVector2D>();
    AddControllerYawInput(Look.X);
    AddControllerPitchInput(Look.Y);
}

void AVHCharacter::FireInput()
{
    if (IsLocallyControlled())
    {
        ServerFire();
    }
}

void AVHCharacter::ApplyCosmeticsVisuals()
{
    const float BodyTint = static_cast<uint8>(RepCosmetics.BodyPreset) / 3.0f;
    const float HeadTint = static_cast<uint8>(RepCosmetics.HeadPreset) / 3.0f;
    const float OutfitTint = static_cast<uint8>(RepCosmetics.OutfitPreset) / 3.0f;

    const FLinearColor NewColor(0.2f + BodyTint, 0.2f + OutfitTint, 0.2f + HeadTint, 1.0f);
    CosmeticProxy->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(NewColor.R, NewColor.G, NewColor.B));
}
