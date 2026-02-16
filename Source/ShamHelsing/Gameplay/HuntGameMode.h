#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HuntGameMode.generated.h"

class ASHMonsterCharacter;

UCLASS()
class SHAMHELSING_API AHuntGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category="Hunt")
    TSubclassOf<ASHMonsterCharacter> MonsterClass;

    UPROPERTY(BlueprintReadOnly)
    ASHMonsterCharacter* SpawnedMonster;

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void CompleteMission(bool bMonsterDefeated);
};
