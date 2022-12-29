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
	//�Ͻ�����
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	//���콺Ŀ��
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	this->RemoveFromParent();


}

void UMenuWidget::RestartGame() {

	//������ �ٽ� �ε��Ѵ�.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("ShoopingMap"));
	//���� ������ �����Ѵ�.
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	this->RemoveFromParent();
}

void UMenuWidget::QuitGame() {

	//�÷��̾� ��Ʈ�ѷ� ��������
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	//���忡�� �÷��̾� ��Ʈ�ѷ��� EQuitPreference::Quit �������� EQuitPreference::Backgound ��׶��� ���� , �������� ��, ����)
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);

}
