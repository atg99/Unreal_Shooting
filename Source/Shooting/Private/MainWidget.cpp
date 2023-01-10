// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingModeBase.h"
#include "Components/TextBlock.h"

void UMainWidget::PrintCurrentScore()
{
	AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(UGameplayStatics::GetGameMode(this));


	if (myGM != nullptr) {
		//현재졈수(정수)를 FTEXT(문자열) 형태로 변환해서 currentScore 텍스트 블록의 값으로 설정한다
		FText scoreTEXT = FText::AsNumber(myGM->GetCurrentScore());

		curScore->SetText(scoreTEXT);

		//최고점수를 문자열로
		FText bscoreTEXT = FText::AsNumber(myGM->GetBestScore());

		bestScore->SetText(bscoreTEXT);
		//scoreAnim을 실행한다    0초부터 1회반복 앞에서부터 실행, 1배속
		//PlayAnimation(scoreAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
	}


}



//void UMainWidget::PrintBestScore()
//{
//	AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(UGameplayStatics::GetGameMode(this));
//
//
//	if (myGM != nullptr) {
//		//현재졈수(정수)를 FTEXT(문자열) 형태로 변환해서 currentScore 텍스트 블록의 값으로 설정한다
//		FText bscoreTEXT = FText::AsNumber(myGM->GetBestScore());
//
//		bestScore->SetText(bscoreTEXT);
//	}
//
//}