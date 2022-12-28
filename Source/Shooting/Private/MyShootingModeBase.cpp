// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShootingModeBase.h"
#include "MainWidget.h"

void AMyShootingModeBase::BeginPlay()
{
	//���� �������Ʈ�� �����Ѵ�.
	UMainWidget* main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	if (main_UI != nullptr) {
		// ������ ������ ����Ʈ�� �׸���
		main_UI->AddToViewport();

		//���� ������ ������ currentScore �ؽ�Ʈ ��Ͽ� �ݿ��Ѵ� 
		main_UI->PrintCurrentScore();
	}
	//������ ������ �� ��Ʈ�� �׸���.

}

void AMyShootingModeBase::AddScore(int32 Count)
{
	currentScore += Count; 
}
