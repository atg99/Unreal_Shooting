// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerFlight.h"
#include "EngineUtils.h"

// Sets default values 생성하기전 before spawn 
AEnemy::AEnemy()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f));
	//Collision Enable 값을 Query and Physics로 설정한다.
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//응답 채널의 Object Type 을 "Enemy"로 설정한다.
	//프로젝트 config - DefaultEngine - ctrl F 콜리전이름
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel2);

	//응답채널을 일괄적으로 ignore 상태로 처리한다
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//응탑채널을 Player와 Bullet 채널에 대해서만 overlap으로 처리한다.
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);
	//콜리전설정을 C++로하면 블루프린트 클래스를 다시만들어야 적용된다.


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	meshComp->SetupAttachment(RootComponent);

	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));

}

// Called when the game starts or when spawned 생성한후
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//충돌처리
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);

	//추첨을 해서 하나는 정면 방향, 또다른 하나는 플레이어 방향으로 이동
	//1.추첨을 한다. 확률은 변수를 이용해서 7:3 비율로 한다.
	INT32 drawNumber = FMath::RandRange(1, 100);
	//2.만일, 0 < rand <= traceRate , 
	//2-1 플레이어의 위치 - 나의 위치 = 플레이어로 가는 위치 
	if (drawNumber <= traceRate) {
		//플레이어 액터를 찾는다.
		// 월드에서 특정한 객체를 찾는 방법 1
		//이터레이터형식의 배열에 모든 엑터를 넣는다; 하나씩 꺼냈을 때 널값이 아니라면 it != unll ; 배열에서 하나씩 뽑는다
		//APlayerFlight* target;
		for (TActorIterator<APlayerFlight> it(GetWorld()); it; ++it) {
			target = *it;
		}
		if (target != nullptr) {
			float temp = target->moveSpeed;
			FVector targetDir = target->GetActorLocation() - GetActorLocation();
			direction = targetDir;
			direction.Normalize();
		}

		//월드에서 특정한 객체를 찾는 방법 2
		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerFlight::StaticClass());

		//FVector targetDir = target->GetActorLocation() - GetActorLocation();
		
		//FVector targetDir = target->GetActorLocation() - GetActorLocation();


		//direction = targetDir;
		//direction.Normalize();
	}
	else {
		//정면이동
		direction = GetActorForwardVector();
	}
	






	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction = GetActorForwardVector();

	SetActorLocation(GetActorLocation() + direction * EnemySpeed * DeltaTime);

}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);
	if (player != nullptr) {
		//player->Destroy();
		player->ReservationHitColor(0.2f);

		Destroy();
	}

}

