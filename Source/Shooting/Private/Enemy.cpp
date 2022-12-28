// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerFlight.h"
#include "EngineUtils.h"

// Sets default values �����ϱ��� before spawn 
AEnemy::AEnemy()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f));
	//Collision Enable ���� Query and Physics�� �����Ѵ�.
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//���� ä���� Object Type �� "Enemy"�� �����Ѵ�.
	//������Ʈ config - DefaultEngine - ctrl F �ݸ����̸�
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel2);

	//����ä���� �ϰ������� ignore ���·� ó���Ѵ�
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//��žä���� Player�� Bullet ä�ο� ���ؼ��� overlap���� ó���Ѵ�.
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);
	//�ݸ��������� C++���ϸ� �������Ʈ Ŭ������ �ٽø����� ����ȴ�.


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	meshComp->SetupAttachment(RootComponent);

	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));

}

// Called when the game starts or when spawned ��������
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//�浹ó��
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);

	//��÷�� �ؼ� �ϳ��� ���� ����, �Ǵٸ� �ϳ��� �÷��̾� �������� �̵�
	//1.��÷�� �Ѵ�. Ȯ���� ������ �̿��ؼ� 7:3 ������ �Ѵ�.
	INT32 drawNumber = FMath::RandRange(1, 100);
	//2.����, 0 < rand <= traceRate , 
	//2-1 �÷��̾��� ��ġ - ���� ��ġ = �÷��̾�� ���� ��ġ 
	if (drawNumber <= traceRate) {
		//�÷��̾� ���͸� ã�´�.
		// ���忡�� Ư���� ��ü�� ã�� ��� 1
		//���ͷ����������� �迭�� ��� ���͸� �ִ´�; �ϳ��� ������ �� �ΰ��� �ƴ϶�� it != unll ; �迭���� �ϳ��� �̴´�
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

		//���忡�� Ư���� ��ü�� ã�� ��� 2
		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerFlight::StaticClass());

		//FVector targetDir = target->GetActorLocation() - GetActorLocation();
		
		//FVector targetDir = target->GetActorLocation() - GetActorLocation();


		//direction = targetDir;
		//direction.Normalize();
	}
	else {
		//�����̵�
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

