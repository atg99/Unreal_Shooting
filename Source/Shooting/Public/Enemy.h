// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SHOOTING_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=EnemySettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemySettings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
		float EnemySpeed = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
		int32 traceRate = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemySettings)
		class UParticleSystem* Explosion_fx;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DestroyMySelf();

	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;

	UFUNCTION()
	void SetNewDirection(FVector evec);

	UFUNCTION()
		void SetNewDirection2(FVector evec);

private:
	FVector direction;
	class APlayerFlight* target;


};
