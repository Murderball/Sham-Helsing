#pragma once
#include "Actors/VHInteractable.h"
#include "VHBaseTerminal.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHBaseTerminal : public AVHInteractable
{
    GENERATED_BODY()
public:
    virtual void ServerInteract(AVHPlayerCharacter* Interactor) override;
};
