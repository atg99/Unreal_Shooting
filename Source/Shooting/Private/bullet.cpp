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

	//�Ѿ� �浹 ������
	boxComp->SetCollisionProfileName(TEXT("BulletPreset"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp -> SetupAttachment(RootComponent);
	//������� ��ġ
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));
}

// Called when the game starts or when spawned
void Abullet::BeginPlay()
{
	Super::BeginPlay();

	//�浹(������)�� �߻��ϸ� ������ �Լ��� �����Ѵ�.
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &Abullet::OnOverlap);
	
	//�������̺�Ʈ�� true�� �����Ѵ�
	boxComp->SetGenerateOverlapEvents(true);
	//boxComp->SetSimulatePhysics(true);

	//�¾ �� 2�� �ڿ� �����Ѵ�
	//SetLifeSpan(2.0f);

	//����Ÿ�̸� ������ �Լ� ����
	//                                                       �������Լ�   �ʼ���, �ݺ�������, 
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
	//���� �ε��� ����� �Ѿ��̶��
	AEnemy* enemy = Cast<AEnemy>(OtherActor); //()�� <>�� ��ȯ�õ� ������ȯ ���� unll

	if (enemy != nullptr) {
		//���� �ִ� ��ġ�� ���� ����Ʈ�� ����
		FVector enemyLoc = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion_effect, enemyLoc, enemyRot, true);
		//������
		enemy->Destroy();

		//���Ӹ���� CurrentScore �߰��Ѵ� ���Ӹ��� � Ŭ���������� �ٷ� ������ �����ϴ�.
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AMyShootingModeBase* myGM = Cast<AMyShootingModeBase>(gm);
		myGM->AddScore(1);
		UE_LOG(LogTemp, Warning, TEXT("Point: %d"), myGM->GetCurrentScore());

		
		//�� �ڽ��� �����Ѵ�
		Destroy();
	}
}

void Abullet::DestroySelf() {
	Destroy();
}

