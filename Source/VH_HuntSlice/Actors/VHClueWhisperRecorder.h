#pragma once
#include "Actors/VHInteractable.h"
#include "VHClueWhisperRecorder.generated.h"

UCLASS()
class VH_HUNTSLICE_API AVHClueWhisperRecorder : public AVHInteractable
{
    GENERATED_BODY()
public:
    virtual void ServerInteract(AVHPlayerCharacter* Interactor) override;
};
