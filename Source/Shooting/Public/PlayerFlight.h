// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//해더에 인클루드는 제러레이티드위에 
#include "InputActionValue.h"
#include "PlayerFlight.generated.h"

UCLASS()
class SHOOTING_API APlayerFlight : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerFlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=playerSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = playerSettings)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = playerSettings)
	TSubclassOf<class Abullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
		class UInputAction* ia_horizontal;
	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
		class UInputAction* ia_vertical;
	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
		class UInputAction* ia_fire;
	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
		class UInputMappingContext* imc_myMapping;
	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
		class USoundBase* fireSound;



private:
	//UFUNCTION(BlueprintCallable)
	//void HorizontalI(float val);

	UFUNCTION(BlueprintCallable)
	void HorizontalI(const FInputActionValue& val);


	UFUNCTION(BlueprintCallable)
	void VerticalI(const FInputActionValue& val);

	//UFUNCTION(BlueprintCallable)
		//void VerticalI(float val);


	UFUNCTION(BlueprintCallable)
	void FireBullet();

	float h;
	float v;

	FVector direction;
	FLinearColor initColor;
	FTimerHandle colorTimer;
	UMaterialInstanceDynamic* my_mat;
	UMaterialInstanceDynamic* dynamicMat;

	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = playerSettings)
	float moveSpeed = 500;

	void ReservationHitColor(float time);
	void ChangeOriginColor();
};
