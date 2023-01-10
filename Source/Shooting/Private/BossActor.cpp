// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyShootingModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "EnemySpawningPool.h"
#include "EngineUtils.h"
#include "EnemyBullet.h"
#include "Components/ArrowComponent.h"

// Sets default values
ABossActor::ABossActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bosBox = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(bosBox);

	bosMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	bosMesh->SetupAttachment(RootComponent);

	arr = CreateDefaultSubobject<UArrowComponent>(TEXT("arr"));
	arr->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABossActor::BeginPlay()
{
	Super::BeginPlay();
	/*AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(gm)
	 
		if (myGM->currentScore >= 30) {
			FTimerHandle TimeerHandle_BossTimer;
			GetWorldTimerManager().SetTimer(TimeerHandle_BossTimer, this, &BossActor:: )
		}*/
	
	startLocation = GetActorLocation();
	endLocation = FVector(-940.0f, -100.0f, 890.0f);

}

// Called every frame
void ABossActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*float distance = (startLocation - GetActorLocation()).Length();
	if (distance < 500) {
		
	}*/


	//if (canMove == true) {
	//	if (GetActorLocation().Z <= 870) {
	//		canMove = false;
	//	}
	//	SetActorLocation(GetActorLocation() - FVector(0, 0, 1 * DeltaTime * 500));
	//}

	//선형보간
	//Clamp 범위지정
	DeltaV = FMath::Clamp(DeltaV, 0.0f, 1.0f);
	if (canMove == true) {
		DeltaV += DeltaTime*0.5;
		FVector result = FMath::Lerp(startLocation, endLocation, DeltaV);
		SetActorLocation(result);

	}

}

void ABossActor::SpawnBoss()
{
	//AActor* pool = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemySpawningPool::StaticClass());
	//AEnemySpawningPool* spawnpool = Cast<AEnemySpawningPool>(pool);
	for (TActorIterator<AEnemySpawningPool> it(GetWorld()); it; ++it) {

		spawn = *it;
		if (spawn != nullptr) {
			spawn->spawnCool = 999.0f;
		}

	}
	//spawnpool->canSpawn = false;
	

	FTimerHandle TimeerHandle_BossTimer;
	GetWorldTimerManager().SetTimer(TimeerHandle_BossTimer, this, &ABossActor::RealSpawn, 4, false);
}

void ABossActor::RealSpawn()
{
	
		canMove = true;
	
	FTimerHandle FTimerHandle_patten1_timer;
	GetWorld()->GetTimerManager().SetTimer(FTimerHandle_patten1_timer, this, &ABossActor::BossAttackCall, 5, true, 3);
}

void ABossActor::BossAttackCall()
{
	BossAttack1(30.0f, 15);
}

void ABossActor::BossAttack1(float angle, int32 count) {

	// angle 간격으로 count 만큼 생성
	UE_LOG(LogTemp, Warning, TEXT("attack"));

	
	for (int32 i = 0; i < count; i++) {

		//원형
		/*FRotator spawnRotation = FRotator(0, (-0.5 * (count - 1) * angle),0);
		FRotator spawnAdd = FRotator(0, angle * i,0);*/

		//무조건 90도
		//float divideAngle = 1 / count;
		FRotator spawnRotation = FRotator(0, -90, 0);
		FRotator spawnAdd = FRotator(0, float(180/(count-2))*i, 0);

		AEnemyBullet* ebull = GetWorld()->SpawnActor<AEnemyBullet>(bulletFactory, arr->GetComponentLocation(), arr->GetComponentRotation());
		ebull->AddActorLocalRotation(spawnRotation + spawnAdd);

		//
	}

}
