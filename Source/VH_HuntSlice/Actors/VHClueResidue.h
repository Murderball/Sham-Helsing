#pragma once
#include "Actors/VHInteractable.h"
#include "VHClueResidue.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHClueResidue : public AVHInteractable
{
    GENERATED_BODY()
public:
    virtual void ServerInteract(AVHPlayerCharacter* Interactor) override;
};
