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
#include "Enemy.h"
#include "EngineUtils.h"
#include "MyShootingModeBase.h"
#include "DrawDebugHelpers.h"



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

	enhancedInputComponent->BindAction(ia_fast, ETriggerEvent::Started, this, &APlayerFlight::Fast);
	enhancedInputComponent->BindAction(ia_fast, ETriggerEvent::Completed, this, &APlayerFlight::Slow);

	enhancedInputComponent->BindAction(ia_ULT, ETriggerEvent::Triggered, this, &APlayerFlight::ExplosionAll);
	enhancedInputComponent->BindAction(ia_ULT, ETriggerEvent::Triggered, this, &APlayerFlight::CheckE);

	//PlayerInputComponent->BindAction("fast", IE_Pressed, this, &APlayerFlight::Fast);
	//PlayerInputComponent->BindAction("fast", IE_Released, this, &APlayerFlight::Slow);

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
	if (isTrap == false) {

		float a = 0;
		for (int i = 0; i < bulletCount; i++) {

			float offset = -0.5 * (bulletCount - 1) * bulletSpacing;


			FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 100.0f+offset*GetActorRightVector()+(GetActorRightVector()*bulletSpacing*i);
			FRotator spawnRotation = FRotator(90.0f, 0, 0);

			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
			Abullet* bullet = GetWorld()->SpawnActor<Abullet>(bulletFactory, spawnPosition, spawnRotation);

			//생성된 총알(bullet)을 bulletAngle 만큼 일정하게 회전시킨다

			FRotator totalAngle = FRotator(0, 0, 0);
			totalAngle = FRotator(0, -0.5 * ((bulletCount - 1) * angle), 0);

			bullet->AddActorLocalRotation(totalAngle+FRotator(0, angle * i,0));

			//총알 발사 효과음
		/*	if (fireSound != nullptr && IsValid(fireSound))
			{
				UGameplayStatics::PlaySound2D(this, fireSound);
				UE_LOG(LogTemp, Warning, TEXT("fire"));
			}*/
		}
	}

}

void APlayerFlight::Fast()
{
	moveSpeed = moveSpeed * 2;
	UE_LOG(LogTemp, Warning, TEXT("fast"));
}

void APlayerFlight::Slow()
{
	moveSpeed = moveSpeed * 0.5f;
	UE_LOG(LogTemp, Warning, TEXT("slow"));
}

void APlayerFlight::ExplosionAll()
{
	//월드에서 에너미를 찾는다 Enemy.h와 #include "EngineUtils.h"
	//TActorIterator를 이용ㅎ한방식
	//for (TActorIterator<AEnemy> it(GetWorld()); it; ++it) {
	//	target = *it;

	//	if (target != nullptr) {

	//		target->DestroyMySelf();
	//	}
	//}

	// TArray<T> 배열을 이용한 방식
	//AMyShootingModeBase* gm = Cast<AMyShootingModeBase>(GetWorld()->GetAuthGameMode());

	//if (gm != nullptr) {

	//	for (int32 i = 0; i < gm->enemies.Num(); i++) {

	//		//Pending kill 상태 체크 IsValid pending kill 부유상태가 아닌 완전삭제
	//		if (IsValid(gm->enemies[i])) {
	//			gm->enemies[i]->DestroyMySelf();
	//		}
	//	}
	//	//리스트를 초기화한다
	//	gm->enemies.Empty();
	//}

	//3. 델리게이트를 실행한다
	playerBomb.Broadcast();
	newDir.Broadcast(FVector(0, 1.0f, 0));

}

void APlayerFlight::CheckE() {

	TArray<FOverlapResult> enemiesInfo;

	//엑터를 기준으로 700
	FVector centerLoc = GetActorLocation() + GetActorUpVector() * 700;

	//퀀트로 변환
	FQuat centerRot = GetActorRotation().Quaternion();

	FCollisionObjectQueryParams params = ECC_GameTraceChannel2;
															//크기
	FCollisionShape checkShape = FCollisionShape::MakeSphere(500);

	//                                   넣을 배열     감지 범위	퀀트값		충돌체널	감지모양
	GetWorld()->OverlapMultiByObjectType(enemiesInfo, centerLoc, centerRot, params, checkShape);

	// 채널 감지
	//GetWorld()->OverlapBlockingTestByProfile()


	//체크된 모든 에너미의 이름을 출력한다 
	for (FOverlapResult enemyinfo : enemiesInfo) {

		UE_LOG(LogTemp, Warning, TEXT("Hited : %s"), *enemyinfo.GetActor()->GetName());

		//충돌한 에너미를 가져온다
		enemyinfo.GetActor()->Destroy();
	}
	
	//콜리전 모양? 을 그린다				   크기,  부드러움, 색, 지속여부, 지속시간
	DrawDebugSphere(GetWorld(), centerLoc, 500, 20, FColor::Yellow, false, 2);

}

