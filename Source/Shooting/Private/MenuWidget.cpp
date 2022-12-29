// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeConstruct()
{
	btn_Re->OnClicked.AddDynamic(this, &UMenuWidget::ResumeGame);
	btn_Re2->OnClicked.AddDynamic(this, &UMenuWidget::RestartGame);
	btn_Re3->OnClicked.AddDynamic(this, &UMenuWidget::QuitGame);
}

void UMenuWidget::ResumeGame()
{
	//일시정지
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	//마우스커서
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	this->RemoveFromParent();


}

void UMenuWidget::RestartGame() {

	//레벨을 다시 로드한다.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("ShoopingMap"));
	//현재 위젯은 제거한다.
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	this->RemoveFromParent();
}

void UMenuWidget::QuitGame() {

	//플레이어 컨트롤러 가져오기
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	//월드에서 플레이어 컨트롤러로 EQuitPreference::Quit 완전종료 EQuitPreference::Backgound 백그라운드 실행 , 강제종료 참, 거짓)
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);

}
