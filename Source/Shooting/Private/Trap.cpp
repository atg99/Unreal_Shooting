// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerFlight.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphere = CreateDefaultSubobject<USphereComponent>(TEXT("sphere"));
	SetRootComponent(sphere);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	meshComp->SetupAttachment(RootComponent);

	sphere->SetCollisionProfileName(TEXT("TrapPreset"));
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	
	
	//overlap 델리게이트에 intrap 함수를 구현
	sphere->OnComponentBeginOverlap.AddDynamic(this, &ATrap::TrapOverlapped);
	//오버랩이 끝날때
	sphere->OnComponentEndOverlap.AddDynamic(this, &ATrap::TrapOverlappedEnd);

	//충돌프리셋을 "TrapPreset" 으로 설정한다
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	cur += DeltaTime;
	if (cur > 2) {
		SetActorLocation(FVector(-972.0f, FMath::RandRange(-960.0f, -1100.0f), FMath::RandRange(600.0f, 800.0f)));

	/*FVector rand_vector = FMath::VRand()* 500;
	rand_vector.X = 0;
	SetActorLocation(rand_vector);*/
	cur = 0;
	}

}

void ATrap::TrapOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	if (player != nullptr)
	{
		player->isTrap = true;
		Intrap();
	}
	UE_LOG(LogTemp, Warning, TEXT("begin"));


}

void ATrap::TrapOverlappedEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);
	if (player != nullptr) {
		player->isTrap = false;
	}
	UE_LOG(LogTemp, Warning, TEXT("end"));
}

void ATrap::Intrap()
{
	//UE_LOG(LogTemp, Warning, TEXT("traped"));
}

