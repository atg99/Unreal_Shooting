// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTT/TEnemyPool.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "TTTT/TestEnemyActor.h"


// Sets default values
ATEnemyPool::ATEnemyPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("ss"));
	SetRootComponent(scene);
	arr = CreateDefaultSubobject<UArrowComponent>(TEXT("arr"));
	arr->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATEnemyPool::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ATEnemyPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	cur += DeltaTime;
	if (cur > 2) {
		GetWorld()->SpawnActor<ATestEnemyActor>(ene, arr->GetComponentLocation(), arr->GetComponentRotation());
		cur = 0;
	}

}

