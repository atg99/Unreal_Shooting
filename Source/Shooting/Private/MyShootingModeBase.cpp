// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShootingModeBase.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "BossActor.h"

void AMyShootingModeBase::BeginPlay()
{
	//위젯 블루프린트를 생성한다.
	main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	if (main_UI != nullptr) {
		// 생성된 위젯을 뷰포트에 그린다
		main_UI->AddToViewport();


		//최고 점수를 파일에서 읽어온다.
		FString scoreText;
		bool isLodeSuccess = FFileHelper::LoadFileToString(scoreText, *filePath);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), isLodeSuccess ? TEXT("Success") : TEXT("Failed"));

		//읽어온 값을 bestScore 텍스트 블록에 반영한다
		bestScore = FCString::Atoi(*scoreText);

		//현재 점수를 위젯의 currentScore 텍스트 블록에 반영한다 
		main_UI->PrintCurrentScore();

	
		
	}
	//생성된 위젯을 뷰 포트에 그린다.

	FString testpath = FPaths::GetProjectFilePath();
	FString testpath2 = FPaths::Combine("https://www.naver.com/", "ssdsd/sfff");
	UE_LOG(LogTemp, Warning, TEXT("test path %s"), *testpath);

	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, TEXT("logTest"), true);


}

void AMyShootingModeBase::AddScore(int32 Count)
{
	currentScore += Count;
	//만일, 누적된 현재 점수가 최고 점수보다 크다면
	//최고 점수에 현재 점수를 넣는다.
	if (bestScore < currentScore) {
		bestScore = currentScore;

		//최고점수를 파일로 저장한다
		
		bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(bestScore), *filePath);

		UE_LOG(LogTemp, Warning, TEXT("%s"), isSaved ? TEXT("True") : TEXT("False")); //삼항연산자
		
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
	//메뉴 위젯을 화면에 표시한다.
	menu_UI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

	if(menu_UI != nullptr){
		menu_UI->AddToViewport();
	}

	//게임을 일시정지 상태로 만든다
	//1.직접 게임의 시간 흐름을 0으로 만든다.
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);

	//2.정지 함수를 호출한다
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	
	//마우스 커서를 화면에 생성한다
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}
