#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSessionSettings.h"
#include "SessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionSearchFinished, const TArray<FString>&, SessionNames);

UCLASS()
class SHAMHELSING_API USessionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void HostSession();

    UFUNCTION(BlueprintCallable)
    void FindSessions();

    UFUNCTION(BlueprintCallable)
    void JoinSessionByIndex(int32 Index);

    UPROPERTY(BlueprintAssignable)
    FOnSessionSearchFinished OnSessionSearchFinished;

private:
    TSharedPtr<FOnlineSessionSearch> Search;
    TArray<FOnlineSessionSearchResult> Results;

    void OnCreateSessionComplete(FName SessionName, bool bSuccess);
    void OnFindSessionsComplete(bool bSuccess);
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
