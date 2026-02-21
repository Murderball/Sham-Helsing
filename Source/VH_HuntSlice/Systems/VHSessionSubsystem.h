#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "VHSessionSubsystem.generated.h"

UCLASS()
class VH_HUNTSLICE_API UVHSessionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void HostSession();

    UFUNCTION(BlueprintCallable)
    void FindAndJoinSession();

private:
    TSharedPtr<FOnlineSessionSearch> SessionSearch;
    IOnlineSessionPtr SessionInterface;

    void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnFindSessionsComplete(bool bWasSuccessful);
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
