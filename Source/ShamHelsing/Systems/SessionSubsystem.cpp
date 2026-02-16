#include "Systems/SessionSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"

void USessionSubsystem::HostSession()
{
    const IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
    if (!OSS) return;

    const IOnlineSessionPtr Session = OSS->GetSessionInterface();
    if (!Session.IsValid()) return;

    FOnlineSessionSettings Settings;
    Settings.bIsLANMatch = true;
    Settings.bShouldAdvertise = true;
    Settings.NumPublicConnections = 4;
    Settings.bUsesPresence = false;
    Settings.bAllowJoinInProgress = true;

    Session->OnCreateSessionCompleteDelegates.AddUObject(this, &USessionSubsystem::OnCreateSessionComplete);
    Session->CreateSession(0, NAME_GameSession, Settings);
}

void USessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
    if (!bSuccess) return;

    if (UWorld* World = GetWorld())
    {
        World->ServerTravel(TEXT("/Game/Maps/Map_Hub?listen"), true);
    }
}

void USessionSubsystem::FindSessions()
{
    const IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
    if (!OSS) return;

    const IOnlineSessionPtr Session = OSS->GetSessionInterface();
    if (!Session.IsValid()) return;

    Search = MakeShared<FOnlineSessionSearch>();
    Search->MaxSearchResults = 20;
    Search->bIsLanQuery = true;

    Session->OnFindSessionsCompleteDelegates.AddUObject(this, &USessionSubsystem::OnFindSessionsComplete);
    Session->FindSessions(0, Search.ToSharedRef());
}

void USessionSubsystem::OnFindSessionsComplete(bool bSuccess)
{
    TArray<FString> Names;
    Results.Empty();

    if (bSuccess && Search.IsValid())
    {
        Results = Search->SearchResults;
        for (int32 i = 0; i < Results.Num(); ++i)
        {
            Names.Add(FString::Printf(TEXT("LAN Session %d"), i));
        }
    }

    OnSessionSearchFinished.Broadcast(Names);
}

void USessionSubsystem::JoinSessionByIndex(int32 Index)
{
    const IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
    if (!OSS || !Results.IsValidIndex(Index)) return;

    const IOnlineSessionPtr Session = OSS->GetSessionInterface();
    if (!Session.IsValid()) return;

    Session->OnJoinSessionCompleteDelegates.AddUObject(this, &USessionSubsystem::OnJoinSessionComplete);
    Session->JoinSession(0, NAME_GameSession, Results[Index]);
}

void USessionSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    const IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
    if (!OSS) return;
    const IOnlineSessionPtr Session = OSS->GetSessionInterface();
    if (!Session.IsValid()) return;

    FString Address;
    if (Session->GetResolvedConnectString(NAME_GameSession, Address))
    {
        if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
        {
            PC->ClientTravel(Address, TRAVEL_Absolute);
        }
    }
}
