#pragma once
#include "Actors/VHInteractable.h"
#include "VHClueSigil.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHClueSigil : public AVHInteractable
{
    GENERATED_BODY()
public:
    virtual void ServerInteract(AVHPlayerCharacter* Interactor) override;
};
