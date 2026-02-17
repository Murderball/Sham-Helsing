#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "VHGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSimpleSessionResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString SessionId;

    UPROPERTY(BlueprintReadOnly)
    FString OwningUserName;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVHSessionOperationComplete, bool, bSuccess);

UCLASS()
class VHPHASMASLICE_API UVHGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;
    virtual void Shutdown() override;

    UPROPERTY(BlueprintAssignable)
    FVHSessionsFound OnSessionsFound;


    UPROPERTY(BlueprintAssignable)
    FVHSessionOperationComplete OnHostComplete;

    UPROPERTY(BlueprintAssignable)
    FVHSessionOperationComplete OnJoinComplete;

    UFUNCTION(BlueprintCallable)
    void HostLANSession(int32 PublicConnections = 4);

    UFUNCTION(BlueprintCallable)
    void FindLANSessions();

    UFUNCTION(BlueprintCallable)
    void JoinSessionByIndex(int32 SessionIndex);

    UFUNCTION(BlueprintCallable)
    void TravelToHubAfterCharacterCreate();

protected:
    void HandleCreateSessionComplete(FName SessionName, bool bWasSuccessful);
    void HandleFindSessionsComplete(bool bWasSuccessful);
    void HandleJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

    IOnlineSessionPtr SessionInterface;
    TSharedPtr<FOnlineSessionSearch> SessionSearch;
    TArray<FOnlineSessionSearchResult> CachedResults;


    FDelegateHandle CreateSessionHandle;
    FDelegateHandle FindSessionsHandle;
    FDelegateHandle JoinSessionHandle;
};
