// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingModeBase.h"
#include "PlayerFlight.h"

AEnemyBullet::AEnemyBullet() {
	boxComp->SetCollisionProfileName(TEXT("Enemy"));
}

void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnOverlap);
}

void AEnemyBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);
	if (player != nullptr) {
		player->Destroy();
		//메뉴 위젯을 생성하는 함수를 실행한다
		AMyShootingModeBase* gm = Cast<AMyShootingModeBase>(GetWorld()->GetAuthGameMode());
		if (gm != nullptr) {
			gm->ShowMenu();
		}
		//GetWorld()->GetTimerManager().SetTimer(,);
		//player->ReservationHitColor(0.2f);

		Destroy();
	}
}

