// Fill out your copyright notice in the Description page of Project Settings.


#include "bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingModeBase.h"

// Sets default values
Abullet::Abullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->SetWorldScale3D(FVector(0.8f, 0.5f, 0.5f));

	//총알 충돌 프리셋
	boxComp->SetCollisionProfileName(TEXT("BulletPreset"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp -> SetupAttachment(RootComponent);
	//상대적인 위치
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));
}

// Called when the game starts or when spawned
void Abullet::BeginPlay()
{
	Super::BeginPlay();

	//충돌(오버랩)이 발생하면 실행할 함수를 연결한다.
	
	//오버랩이벤트를 true로 설정한다
	boxComp->SetGenerateOverlapEvents(true);
	//boxComp->SetSimulatePhysics(true);

	//태어난 후 2초 뒤에 제거한다
	//SetLifeSpan(2.0f);

	//월드타이머 설정한 함수 실행
	//                                                       실행할함수   초설정, 반복참거짓, 
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &Abullet::DestroySelf, 2.0f, false);
}

// Called every frame
void Abullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction = FVector(1, 0, 0); world direction
	direction = GetActorForwardVector();

	SetActorLocation(GetActorLocation() + direction * bulletSpeed * DeltaTime);


}



void Abullet::DestroySelf() {
	Destroy();
}

