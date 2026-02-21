#include "Systems/VHSessionSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"

void UVHSessionSubsystem::HostSession()
{
    if (IOnlineSubsystem* OSS = IOnlineSubsystem::Get())
    {
        SessionInterface = OSS->GetSessionInterface();
    }
    if (!SessionInterface.IsValid())
    {
        return;
    }

    FOnlineSessionSettings Settings;
    Settings.bIsLANMatch = true;
    Settings.bUsesPresence = false;
    Settings.NumPublicConnections = 4;
    Settings.bShouldAdvertise = true;

    SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UVHSessionSubsystem::OnCreateSessionComplete);
    SessionInterface->CreateSession(0, NAME_GameSession, Settings);
}

void UVHSessionSubsystem::FindAndJoinSession()
{
    if (IOnlineSubsystem* OSS = IOnlineSubsystem::Get())
    {
        SessionInterface = OSS->GetSessionInterface();
    }
    if (!SessionInterface.IsValid())
    {
        return;
    }

    SessionSearch = MakeShared<FOnlineSessionSearch>();
    SessionSearch->bIsLanQuery = true;
    SessionSearch->MaxSearchResults = 20;

    SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UVHSessionSubsystem::OnFindSessionsComplete);
    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UVHSessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/VH/Maps/Map_BaseHub"), true, TEXT("listen"));
    }
}

void UVHSessionSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
    if (!bWasSuccessful || !SessionInterface.IsValid() || !SessionSearch.IsValid() || SessionSearch->SearchResults.IsEmpty())
    {
        return;
    }

    SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UVHSessionSubsystem::OnJoinSessionComplete);
    SessionInterface->JoinSession(0, NAME_GameSession, SessionSearch->SearchResults[0]);
}

void UVHSessionSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    FString ConnectString;
    if (Result == EOnJoinSessionCompleteResult::Success && SessionInterface->GetResolvedConnectString(SessionName, ConnectString))
    {
        if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
        {
            PC->ClientTravel(ConnectString, TRAVEL_Absolute);
        }
    }
}
