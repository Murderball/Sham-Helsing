#include "Core/VHGameInstance.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

void UVHGameInstance::Init()
{
    Super::Init();

    if (IOnlineSubsystem* OSS = IOnlineSubsystem::Get())
    {
        SessionInterface = OSS->GetSessionInterface();
    }
}

void UVHGameInstance::Shutdown()
{
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionHandle);
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsHandle);
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionHandle);
    }

    Super::Shutdown();
}

void UVHGameInstance::HostLANSession(int32 PublicConnections)
{
    if (!SessionInterface.IsValid())
    {
        OnHostComplete.Broadcast(false);
        return;
    }

    FOnlineSessionSettings Settings;
    Settings.bIsLANMatch = true;
    Settings.bShouldAdvertise = true;
    Settings.bUsesPresence = true;
    Settings.NumPublicConnections = PublicConnections;

    CreateSessionHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
        FOnCreateSessionCompleteDelegate::CreateUObject(this, &UVHGameInstance::HandleCreateSessionComplete));

    SessionInterface->CreateSession(0, NAME_GameSession, Settings);
}

void UVHGameInstance::FindLANSessions()
{
    if (!SessionInterface.IsValid())
    {

        return;
    }

    SessionSearch = MakeShared<FOnlineSessionSearch>();
    SessionSearch->MaxSearchResults = 32;
    SessionSearch->bIsLanQuery = true;

    FindSessionsHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(
        FOnFindSessionsCompleteDelegate::CreateUObject(this, &UVHGameInstance::HandleFindSessionsComplete));

    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UVHGameInstance::JoinSessionByIndex(int32 SessionIndex)
{
    if (!SessionInterface.IsValid() || !CachedResults.IsValidIndex(SessionIndex))
    {
        OnJoinComplete.Broadcast(false);
        return;
    }

    JoinSessionHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
        FOnJoinSessionCompleteDelegate::CreateUObject(this, &UVHGameInstance::HandleJoinSessionComplete));

    SessionInterface->JoinSession(0, NAME_GameSession, CachedResults[SessionIndex]);
}

void UVHGameInstance::TravelToHubAfterCharacterCreate()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    if (World->GetNetMode() == NM_Standalone)
    {
        HostLANSession();
        return;
    }

    GetFirstLocalPlayerController()->ClientTravel(TEXT("/Game/Maps/L_BaseHub"), TRAVEL_Absolute);
}

void UVHGameInstance::HandleCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionHandle);
    }

    OnHostComplete.Broadcast(bWasSuccessful);

    if (bWasSuccessful)
    {
        if (UWorld* World = GetWorld())
        {
            World->ServerTravel(TEXT("/Game/Maps/L_BaseHub?listen"));
        }
    }
}

void UVHGameInstance::HandleFindSessionsComplete(bool bWasSuccessful)
{
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsHandle);
    }

    CachedResults.Reset();

    if (bWasSuccessful && SessionSearch.IsValid())
    {
        CachedResults = SessionSearch->SearchResults;

        for (const FOnlineSessionSearchResult& Result : CachedResults)
        {
            FSimpleSessionResult Item;
            Item.SessionId = Result.GetSessionIdStr();
            Item.OwningUserName = Result.Session.OwningUserName;


void UVHGameInstance::HandleJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionHandle);
    }

    const bool bSuccess = Result == EOnJoinSessionCompleteResult::Success;
    OnJoinComplete.Broadcast(bSuccess);

    if (!bSuccess)
    {
        return;
    }

    FString ConnectString;
    if (SessionInterface->GetResolvedConnectString(SessionName, ConnectString))
    {
        if (APlayerController* PC = GetFirstLocalPlayerController())
        {
            PC->ClientTravel(ConnectString, TRAVEL_Absolute);
        }
    }
}
