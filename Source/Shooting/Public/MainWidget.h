// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	//���ھ� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta=(BindWidget))
	class UTextBlock* curScore;

	UPROPERTY(EditAnywhere, Category = "MySetting|Score", meta = (BindWidget))
	class UTextBlock* bestScore;
																			//�ִϸ��̼��� Transient �߰�
	/*UPROPERTY(EditAnywhere, Category = "MySetting|Score", meta = (BindWidget), Transient)
	class UWidgetAnimation* scoreAnim;*/


	void PrintCurrentScore();
	void PrintBestScore();
};
