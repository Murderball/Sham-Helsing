#pragma once
#include "Actors/VHInteractable.h"
#include "VHBanishAltar.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHBanishAltar : public AVHInteractable
{
    GENERATED_BODY()
public:
    virtual void ServerInteract(AVHPlayerCharacter* Interactor) override;
};
