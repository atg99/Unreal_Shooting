// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestEnemyActor.generated.h"

UCLASS()
class SHOOTING_API ATestEnemyActor : public AActor
{
	GENERATED_BODY()
		

	
public:	
	// Sets default values for this actor's properties
	ATestEnemyActor();

	UPROPERTY(EditAnywhere)
		class UBoxComponent* box;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
