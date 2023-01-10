// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossActor.generated.h"

UCLASS()
class SHOOTING_API ABossActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = BossSetting)
		class UBoxComponent* bosBox;

	UPROPERTY(EditAnywhere, Category = BossSetting)
		class UStaticMeshComponent* bosMesh;

	UPROPERTY(EditAnywhere, Category = BossSetting)
		class UArrowComponent* arr;

	UPROPERTY(EditAnywhere, Category = BossSetting)
	TSubclassOf<class AEnemyBullet> bulletFactory;

	UFUNCTION()
	void SpawnBoss();
	UFUNCTION()
	void RealSpawn();

	bool canMove=false;


private:
	class AEnemySpawningPool* spawn;

	FVector startLocation;
	FVector endLocation;

	float DeltaV;

	void BossAttackCall();

	UFUNCTION()
	void BossAttack1(float angle, int32 count);
};
