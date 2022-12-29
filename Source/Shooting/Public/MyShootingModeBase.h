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
	FORCEINLINE int32 GetCurrentScore() {return currentScore;} //�ζ����Լ� ���ٸ�����

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetBestScore() { return bestScore; } //�ζ����Լ� ���ٸ�����

	UPROPERTY(EditAnywhere, Category=MyDefaultSetting)
	TSubclassOf<class UMainWidget> mainWidget;

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
		TSubclassOf<class UMenuWidget> menuWidget;

	virtual void BeginPlay() override;

	void AddScore(int32 Count);

	void ShowMenu();

private:
	
	//UPROPERTY(BlueprintReadWrite)
	//���ھ� ����
	int32 currentScore = 0;

	int32 bestScore = 0;
	class UMainWidget* main_UI;
	class UMenuWidget* menu_UI;

	FString filePath = FString("D:/Git/Valorant_Copy/Content/SaveScore/BestScore.txt");


};
