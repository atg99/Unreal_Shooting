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

		//박스 콜리전의 총돌 처리 프리셋을 "PlayerPreset"으로 설정한다.
		boxComp->SetCollisionProfileName(TEXT("PlayerPreset"));

		//메시 컴포넌트의 Static mesh 항목의 큐브 파일을 할당한다.
		ConstructorHelpers::FObjectFinder<UStaticMesh> triMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_TriPyramid.Shape_TriPyramid'"));

		//만일 큐브 파일을 로드하는데 성고앻ㅆ다면
		if (triMesh.Succeeded())
		{
			//로드한 파일을 메시 컴포넌트의 static mesh 항목에 넣는다
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

	//메터리얼 배열 0을 저장한다
	UMaterialInterface* imat = meshComp->GetMaterial(0);
	FHashedMaterialParameterInfo param = FHashedMaterialParameterInfo(TEXT("myColor"));

	//Material interface에서 백터 파라미터 값을 initcolor 변수에 저장
	imat->GetVectorParameterValue(param, initColor);
	UE_LOG(LogTemp, Warning, TEXT("R : %f G:%f B:%f"), initColor.R, initColor.G, initColor.B);

	//Material interface를 이용해서 material instance Dynamic 개채를 생성한다. 
	dynamicMat = UMaterialInstanceDynamic::Create(imat, this);
	//my_mat->GetVectorParameterValue(param, (FLinearColor)initColor);
	//생성한 다이나믹 메시를 생성한다?

	if (dynamicMat != nullptr) {
		meshComp->SetMaterial(0, dynamicMat);
	}

}

// Called every frame
void APlayerFlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//사용자가 입력한 방향대로 이동
	// p = p0 +vt
	direction.Normalize();
	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;

	//Block 물리에서 : true 충돌하는지 확인 하고간다 false 충동확인안함
	SetActorLocation(dir, true);

}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//기존의 UInputComponent* 변수를 
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//함수연결
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Triggered, this, &APlayerFlight::HorizontalI);

	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Completed, this, &APlayerFlight::HorizontalI);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Triggered, this, &APlayerFlight::VerticalI);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Completed, this, &APlayerFlight::VerticalI);

	enhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Triggered, this, &APlayerFlight::FireBullet);

	//Horizontal Axis 입력에 함수를 연결한다.
	//PlayerInputComponent->BindAxis("Horizontal", this, &APlayerFlight::HorizontalI);
	//Vertical Axis 입력에 함수를 연결한다.
	//PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::VerticalI);

	//PlayerInputComponent->BindAction("Firing", IE_Pressed, this, &APlayerFlight::FireBullet);

}

void APlayerFlight::ReservationHitColor(float time)
{
	dynamicMat->SetVectorParameterValue(TEXT("myColor"), (FVector4)FLinearColor::Red);


	
	GetWorld()->GetTimerManager().SetTimer(colorTimer, this, &APlayerFlight::ChangeOriginColor, time, false);
}

//부딪혔을 때 색을 0.6초동안 바꾸는 함수
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
	//총알 스폰
	//총알 플루프린트 변수
	FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 100.0f;
	FRotator spawnRotation = FRotator(90.0f, 0, 0);
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<Abullet>(bulletFactory, spawnPosition, spawnRotation);
	//총알 발사 효과음
	UGameplayStatics::PlaySound2D(this, fireSound);
}

