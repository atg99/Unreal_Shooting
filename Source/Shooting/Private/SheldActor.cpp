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
	//������ ���Ͱ� �������
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	if (enemy != nullptr) {
		enemy->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("sdsd"));
	}

	player = Cast<APlayerFlight>(OtherActor);
	if (player != nullptr) {
		
		//attach to �ϸ� �ڽ����� �����ȴ�. attach to actor�� �ϸ� ������ ��Ʈ�� ���� 
		//attach to component�ϸ� Ư�� ������Ʈ�� ����
		//             FAttachmentTransformRules ����ġ ��Ģ ���� keep�� ���� ������ �����ϸ鼭 �̵�
		//														Snap�� �Ǻ��������� ��ģ��
		this->AttachToActor(player, FAttachmentTransformRules::KeepWorldTransform);
		
		//player->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

		FTimerHandle AttachTimer;
		GetWorldTimerManager().SetTimer(AttachTimer, this, &ASheldActor::ResetAttach, 3.0f);
		
	}


}

void ASheldActor::ResetAttach()
{
	// �ٿ����� �θ� ����, �θ� ������ �ֱ� ������ �θ����� x
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

	//												1�ʿ� 10����
	//SetActorRotation(GetActorRotation() + FRotator(10.0f * DeltaTime, 10.0f*DeltaTime, 10.0f * DeltaTime));

	AddActorLocalRotation(FRotator(10.0f * DeltaTime, 10.0f * DeltaTime, 10.0f * DeltaTime));
}

