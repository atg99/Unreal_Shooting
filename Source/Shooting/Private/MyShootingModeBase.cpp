// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShootingModeBase.h"
#include "MainWidget.h"

void AMyShootingModeBase::BeginPlay()
{
	//위젯 블루프린트를 생성한다.
	UMainWidget* main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	if (main_UI != nullptr) {
		// 생성된 위젯을 뷰포트에 그린다
		main_UI->AddToViewport();

		//현재 점수를 위젯의 currentScore 텍스트 블록에 반영한다 
		main_UI->PrintCurrentScore();
	}
	//생성된 위젯을 뷰 포트에 그린다.

}

void AMyShootingModeBase::AddScore(int32 Count)
{
	currentScore += Count; 
}
