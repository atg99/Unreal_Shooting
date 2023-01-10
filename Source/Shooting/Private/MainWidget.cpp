// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingModeBase.h"
#include "Components/TextBlock.h"

void UMainWidget::PrintCurrentScore()
{
	AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(UGameplayStatics::GetGameMode(this));


	if (myGM != nullptr) {
		//��������(����)�� FTEXT(���ڿ�) ���·� ��ȯ�ؼ� currentScore �ؽ�Ʈ ����� ������ �����Ѵ�
		FText scoreTEXT = FText::AsNumber(myGM->GetCurrentScore());

		curScore->SetText(scoreTEXT);

		//�ְ������� ���ڿ���
		FText bscoreTEXT = FText::AsNumber(myGM->GetBestScore());

		bestScore->SetText(bscoreTEXT);
		//scoreAnim�� �����Ѵ�    0�ʺ��� 1ȸ�ݺ� �տ������� ����, 1���
		//PlayAnimation(scoreAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
	}


}



//void UMainWidget::PrintBestScore()
//{
//	AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(UGameplayStatics::GetGameMode(this));
//
//
//	if (myGM != nullptr) {
//		//��������(����)�� FTEXT(���ڿ�) ���·� ��ȯ�ؼ� currentScore �ؽ�Ʈ ����� ������ �����Ѵ�
//		FText bscoreTEXT = FText::AsNumber(myGM->GetBestScore());
//
//		bestScore->SetText(bscoreTEXT);
//	}
//
//}