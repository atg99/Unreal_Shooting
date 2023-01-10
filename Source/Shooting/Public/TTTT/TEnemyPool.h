// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TEnemyPool.generated.h"

UCLASS()
class SHOOTING_API ATEnemyPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATEnemyPool();
	UPROPERTY(EditAnywhere)
	class USceneComponent* scene;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* arr;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATestEnemyActor> ene;

	float cur;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
