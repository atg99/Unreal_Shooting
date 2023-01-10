// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingModeBase.h"

APlayerBullet::APlayerBullet()
{

}

void APlayerBullet::BeginPlay()
{
	//super �ٷ��� �θ�
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnOverlap);
}

void APlayerBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//���� �ε��� ����� ���̶��
	AEnemy* enemy = Cast<AEnemy>(OtherActor); //()�� <>�� ��ȯ�õ� ������ȯ ���� unll

	if (enemy != nullptr) {
		//���� �ִ� ��ġ�� ���� ����Ʈ�� ����
		FVector enemyLoc = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion_effect, enemyLoc, enemyRot, true);
		//������
		enemy->Destroy();

		//���Ӹ���� CurrentScore �߰��Ѵ� ���Ӹ��� � Ŭ���������� �ٷ� ������ �����ϴ�.

		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		//AGameModeBase* gm = GetWorld()->GetAuthGameMode(); �ι�° ���

		AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(gm);

		myGM->AddScore(1);
		UE_LOG(LogTemp, Warning, TEXT("Point: %d"), myGM->GetCurrentScore());


		//�� �ڽ��� �����Ѵ�
		Destroy();
	}
}
