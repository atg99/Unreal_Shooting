// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlight.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Uobject/ConstructorHelpers.h"
#include "bullet.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
APlayerFlight::APlayerFlight()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Compent"));

		SetRootComponent(boxComp);

		meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));

		meshComp->SetupAttachment(RootComponent);

		FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
		boxComp->SetBoxExtent(boxSize);

		//�ڽ� �ݸ����� �ѵ� ó�� �������� "PlayerPreset"���� �����Ѵ�.
		boxComp->SetCollisionProfileName(TEXT("PlayerPreset"));

		//�޽� ������Ʈ�� Static mesh �׸��� ť�� ������ �Ҵ��Ѵ�.
		ConstructorHelpers::FObjectFinder<UStaticMesh> triMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_TriPyramid.Shape_TriPyramid'"));

		//���� ť�� ������ �ε��ϴµ� �����ٸ�
		if (triMesh.Succeeded())
		{
			//�ε��� ������ �޽� ������Ʈ�� static mesh �׸� �ִ´�
			meshComp->SetStaticMesh(triMesh.Object);;
		}

}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerCon = Cast<APlayerController>(GetController());
	
	if (playerCon != nullptr) {
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());


		if (subsys != nullptr) {
			subsys->AddMappingContext(imc_myMapping, 0);
		}
	}

	//���͸��� �迭 0�� �����Ѵ�
	UMaterialInterface* imat = meshComp->GetMaterial(0);
	FHashedMaterialParameterInfo param = FHashedMaterialParameterInfo(TEXT("myColor"));

	//Material interface���� ���� �Ķ���� ���� initcolor ������ ����
	imat->GetVectorParameterValue(param, initColor);
	UE_LOG(LogTemp, Warning, TEXT("R : %f G:%f B:%f"), initColor.R, initColor.G, initColor.B);

	//Material interface�� �̿��ؼ� material instance Dynamic ��ä�� �����Ѵ�. 
	dynamicMat = UMaterialInstanceDynamic::Create(imat, this);
	//my_mat->GetVectorParameterValue(param, (FLinearColor)initColor);
	//������ ���̳��� �޽ø� �����Ѵ�?

	if (dynamicMat != nullptr) {
		meshComp->SetMaterial(0, dynamicMat);
	}

}

// Called every frame
void APlayerFlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//����ڰ� �Է��� ������ �̵�
	// p = p0 +vt
	direction.Normalize();
	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;

	//Block �������� : true �浹�ϴ��� Ȯ�� �ϰ��� false �浿Ȯ�ξ���
	SetActorLocation(dir, true);

}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//������ UInputComponent* ������ 
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//�Լ�����
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Triggered, this, &APlayerFlight::HorizontalI);

	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Completed, this, &APlayerFlight::HorizontalI);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Triggered, this, &APlayerFlight::VerticalI);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Completed, this, &APlayerFlight::VerticalI);

	enhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Triggered, this, &APlayerFlight::FireBullet);

	//Horizontal Axis �Է¿� �Լ��� �����Ѵ�.
	//PlayerInputComponent->BindAxis("Horizontal", this, &APlayerFlight::HorizontalI);
	//Vertical Axis �Է¿� �Լ��� �����Ѵ�.
	//PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::VerticalI);

	//PlayerInputComponent->BindAction("Firing", IE_Pressed, this, &APlayerFlight::FireBullet);

}

void APlayerFlight::ReservationHitColor(float time)
{
	dynamicMat->SetVectorParameterValue(TEXT("myColor"), (FVector4)FLinearColor::Red);


	
	GetWorld()->GetTimerManager().SetTimer(colorTimer, this, &APlayerFlight::ChangeOriginColor, time, false);
}

//�ε����� �� ���� 0.6�ʵ��� �ٲٴ� �Լ�
//void APlayerFlight::ChangeHitColor()
//{
//	UMaterialInstanceDynamic* my_mat = Cast<UMaterialInstanceDynamic>(meshComp->GetMaterial(0));
//
//	my_mat->SetVectorParameterValue(TEXT("myColor"), FLinearColor::Red);
//	//my_mat->SetVectorParameterValue(TEXT("myColor"), FLinearColor(255, 0, 0, 255));
//}

void APlayerFlight::ChangeOriginColor()
{
	dynamicMat->SetVectorParameterValue(TEXT("myColor"), initColor);
}
//void APlayerFlight::HorizontalI(float val)
//{
//	h = val;
//	//UE_LOG(LogTemp, Warning, TEXT("h : %.4f"), h);
//	direction.Y = h;
//}

void APlayerFlight::HorizontalI(const FInputActionValue& val)
{
	h = val.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("h : %.4f"), h);
	direction.Y = h;
}

//void APlayerFlight::VerticalI(float val)
//{
//	v = val;
//	//UE_LOG(LogTemp, Warning, TEXT("v : %.4f"), v);
//	direction.Z = v;
//}

void APlayerFlight::VerticalI(const FInputActionValue& val)
{
	v = val.Get<float>();
	direction.Z = v;
}

void APlayerFlight::FireBullet()
{
	//�Ѿ� ����
	//�Ѿ� �÷�����Ʈ ����
	FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 100.0f;
	FRotator spawnRotation = FRotator(90.0f, 0, 0);
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<Abullet>(bulletFactory, spawnPosition, spawnRotation);
	//�Ѿ� �߻� ȿ����
	UGameplayStatics::PlaySound2D(this, fireSound);
}

