// Fill out your copyright notice in the Description page of Project Settings.


#include "bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingModeBase.h"

// Sets default values
Abullet::Abullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->SetWorldScale3D(FVector(0.8f, 0.5f, 0.5f));

	//총알 충돌 프리셋
	boxComp->SetCollisionProfileName(TEXT("BulletPreset"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp -> SetupAttachment(RootComponent);
	//상대적인 위치
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));
}

// Called when the game starts or when spawned
void Abullet::BeginPlay()
{
	Super::BeginPlay();

	//충돌(오버랩)이 발생하면 실행할 함수를 연결한다.
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &Abullet::OnOverlap);
	
	//오버랩이벤트를 true로 설정한다
	boxComp->SetGenerateOverlapEvents(true);
	//boxComp->SetSimulatePhysics(true);

	//태어난 후 2초 뒤에 제거한다
	//SetLifeSpan(2.0f);

	//월드타이머 설정한 함수 실행
	//                                                       실행할함수   초설정, 반복참거짓, 
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &Abullet::DestroySelf, 2.0f, false);
}

// Called every frame
void Abullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction = FVector(1, 0, 0); world direction
	direction = GetActorForwardVector();

	SetActorLocation(GetActorLocation() + direction * bulletSpeed * DeltaTime);


}

void Abullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//만일 부딪힌 대상이 총알이라면
	AEnemy* enemy = Cast<AEnemy>(OtherActor); //()를 <>로 변환시도 성공반환 실패 unll

	if (enemy != nullptr) {
		//적이 있던 위치에 폭발 이팩트를 생성
		FVector enemyLoc = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion_effect, enemyLoc, enemyRot, true);
		//적제거
		enemy->Destroy();

		//게임모드의 CurrentScore 추가한다 게임모드는 어떤 클레스에서든 바로 접근이 가능하다.
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(gm);
		myGM->AddScore(1);
		UE_LOG(LogTemp, Warning, TEXT("Point: %d"), myGM->GetCurrentScore());

		
		//나 자신을 제거한다
		Destroy();
	}
}

void Abullet::DestroySelf() {
	Destroy();
}

