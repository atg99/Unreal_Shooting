// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShootingModeBase.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "BossActor.h"

void AMyShootingModeBase::BeginPlay()
{
	//���� �������Ʈ�� �����Ѵ�.
	main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	if (main_UI != nullptr) {
		// ������ ������ ����Ʈ�� �׸���
		main_UI->AddToViewport();


		//�ְ� ������ ���Ͽ��� �о�´�.
		FString scoreText;
		bool isLodeSuccess = FFileHelper::LoadFileToString(scoreText, *filePath);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), isLodeSuccess ? TEXT("Success") : TEXT("Failed"));

		//�о�� ���� bestScore �ؽ�Ʈ ��Ͽ� �ݿ��Ѵ�
		bestScore = FCString::Atoi(*scoreText);

		//���� ������ ������ currentScore �ؽ�Ʈ ��Ͽ� �ݿ��Ѵ� 
		main_UI->PrintCurrentScore();

	
		
	}
	//������ ������ �� ��Ʈ�� �׸���.

	FString testpath = FPaths::GetProjectFilePath();
	FString testpath2 = FPaths::Combine("https://www.naver.com/", "ssdsd/sfff");
	UE_LOG(LogTemp, Warning, TEXT("test path %s"), *testpath);

	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, TEXT("logTest"), true);


}

void AMyShootingModeBase::AddScore(int32 Count)
{
	currentScore += Count;
	//����, ������ ���� ������ �ְ� �������� ũ�ٸ�
	//�ְ� ������ ���� ������ �ִ´�.
	if (bestScore < currentScore) {
		bestScore = currentScore;

		//�ְ������� ���Ϸ� �����Ѵ�
		
		bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(bestScore), *filePath);

		UE_LOG(LogTemp, Warning, TEXT("%s"), isSaved ? TEXT("True") : TEXT("False")); //���׿�����
		
	}
	if (main_UI != nullptr) {

		main_UI->PrintCurrentScore();

	}

	if (currentScore >= 30) {

		GetWorld()->SpawnActor<ABossActor>(bossFactory, FVector((-940.0f, 120.0f, 2500.0f)), FRotator::ZeroRotator);

		AActor* bossActor = UGameplayStatics::GetActorOfClass(GetWorld(), ABossActor::StaticClass());
		ABossActor* boss = Cast<ABossActor>(bossActor);
		boss->SpawnBoss();
	}
	
}

void AMyShootingModeBase::ShowMenu()
{
	//�޴� ������ ȭ�鿡 ǥ���Ѵ�.
	menu_UI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

	if(menu_UI != nullptr){
		menu_UI->AddToViewport();
	}

	//������ �Ͻ����� ���·� �����
	//1.���� ������ �ð� �帧�� 0���� �����.
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);

	//2.���� �Լ��� ȣ���Ѵ�
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	
	//���콺 Ŀ���� ȭ�鿡 �����Ѵ�
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}
