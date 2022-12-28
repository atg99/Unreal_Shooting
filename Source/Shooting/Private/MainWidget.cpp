// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingModeBase.h"
#include "Components/TextBlock.h"

void UMainWidget::PrintCurrentScore()
{
	AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(UGameplayStatics::GetGameMode(this));

	if (myGM != nullptr) {
		//��������(����)�� FTEXT(���ڿ�) ���·� ��ȯ�ؼ� currentScore �ؽ�Ʈ ������ ������ �����Ѵ�
		FText scoreTEXT = FText::AsNumber(myGM->GetCurrentScore());

		curScore->SetText(scoreTEXT);
	}

}