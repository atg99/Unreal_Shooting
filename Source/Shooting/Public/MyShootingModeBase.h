// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyShootingModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API AMyShootingModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentScore() {return currentScore;} //인라인함수 한줄만가능

	UPROPERTY(EditAnywhere, Category=MyDefaultSetting)
	TSubclassOf<class UMainWidget> mainWidget;

	virtual void BeginPlay() override;

	void AddScore(int32 Count);

private:
	
	//UPROPERTY(BlueprintReadWrite)
	int32 currentScore = 0;


};
