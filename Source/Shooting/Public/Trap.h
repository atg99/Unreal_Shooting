// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class SHOOTING_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//USphereComponent�� ��Ʈ �ݸ����� �����Ѵ�
	UPROPERTY(EditAnywhere)
	class USphereComponent* sphere;
	//UStaticmesh�� �ڽ� ���� ����
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
	//Intrap �Լ� ����

	UFUNCTION()
		void TrapOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TrapOverlappedEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Intrap();

private:
	float cur;
};