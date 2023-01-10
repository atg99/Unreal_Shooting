// Fill out your copyright notice in the Description page of Project Settings.


#include "SheldActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerFlight.h"
#include "Enemy.h"

// Sets default values
ASheldActor::ASheldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("box collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50, 150, 50));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);
	//meshComp->(FVector(50, 150, 50));
}

void ASheldActor::ShieldOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//닿으면 엑터가 사라지게
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	if (enemy != nullptr) {
		enemy->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("sdsd"));
	}

	player = Cast<APlayerFlight>(OtherActor);
	if (player != nullptr) {
		
		//attach to 하면 자식으로 설정된다. attach to actor로 하면 엑터의 루트에 붙임 
		//attach to component하면 특정 컴포넌트에 붙임
		//             FAttachmentTransformRules 어테치 규칙 설정 keep은 같은 간격을 유지하면서 이동
		//														Snap은 피봇기준으로 겹친다
		this->AttachToActor(player, FAttachmentTransformRules::KeepWorldTransform);
		
		//player->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

		FTimerHandle AttachTimer;
		GetWorldTimerManager().SetTimer(AttachTimer, this, &ASheldActor::ResetAttach, 3.0f);
		
	}


}

void ASheldActor::ResetAttach()
{
	// 붙여놨던 부모를 해제, 부모가 무조건 있기 때문에 부모지정 x
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void ASheldActor::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ASheldActor::ShieldOverlapped);
}

// Called every frame
void ASheldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//												1초에 10도씩
	//SetActorRotation(GetActorRotation() + FRotator(10.0f * DeltaTime, 10.0f*DeltaTime, 10.0f * DeltaTime));

	AddActorLocalRotation(FRotator(10.0f * DeltaTime, 10.0f * DeltaTime, 10.0f * DeltaTime));
}

