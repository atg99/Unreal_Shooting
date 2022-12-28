// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "bullet.generated.h"

UCLASS()
class SHOOTING_API Abullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Abullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
		class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
		float bulletSpeed=1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
	class UParticleSystem* Explosion_effect;
	//��������Ʈ�θ��� �Լ����� UFUNTioN���� ����
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector direction;
	FTimerHandle lifeTimer;

	void DestroySelf();
};