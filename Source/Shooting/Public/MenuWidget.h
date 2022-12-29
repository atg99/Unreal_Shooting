// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	class UButton* btn_Re;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Re2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Re3;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void QuitGame();
};
