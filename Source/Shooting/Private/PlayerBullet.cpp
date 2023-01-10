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
	//super 바로위 부모
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnOverlap);
}

void APlayerBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//만일 부딪힌 대상이 적이라면
	AEnemy* enemy = Cast<AEnemy>(OtherActor); //()를 <>로 변환시도 성공반환 실패 unll

	if (enemy != nullptr) {
		//적이 있던 위치에 폭발 이팩트를 생성
		FVector enemyLoc = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion_effect, enemyLoc, enemyRot, true);
		//적제거
		enemy->Destroy();

		//게임모드의 CurrentScore 추가한다 게임모드는 어떤 클레스에서든 바로 접근이 가능하다.

		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		//AGameModeBase* gm = GetWorld()->GetAuthGameMode(); 두번째 방법

		AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(gm);

		myGM->AddScore(1);
		UE_LOG(LogTemp, Warning, TEXT("Point: %d"), myGM->GetCurrentScore());


		//나 자신을 제거한다
		Destroy();
	}
}
