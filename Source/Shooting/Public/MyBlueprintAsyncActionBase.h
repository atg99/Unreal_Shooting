// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "MyBlueprintAsyncActionBase.generated.h"

/**
 * 
 */

//���ε��̺�Ʈ�� �ɶ� ���� ���� 2��      ��������Ʈ �Լ��� �Ķ���� Ÿ�� �̸��� , �� �����Ѵ�.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTTDelegate, int32, Id, FString, Data, bool, Info);


UCLASS()
class SHOOTING_API UMyBlueprintAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintASSignable)  //��������Ʈ���� ����ϰڴ�? ��������Ʈ ���
		FTTDelegate OnSuccess; // FTTDelegate���� ����� ���� ����

	UPROPERTY(BlueprintAssignable)
		FTTDelegate OnFail; 

	UPROPERTY(BlueprintAssignable)
		FTTDelegate Unknownn;

	UPROPERTY() //��������Ƽ�� ������ ������ �÷��Ͱ� 60�ʸ��� �����ؼ� null�� �ǹ�����!
		int32 temp;
	UFUNCTION(BlueprintCallable, Meta = (BlueprintInternalUseOnly = "true")) //������ �ִ� �Լ�
		static UMyBlueprintAsyncActionBase* AsyncTest(const int ID);

	virtual void Activate() override; // override��? �ڼ��� �θ� �Լ��� �ڱⰡ ���ϴ� ��� �ٲ㼭 ���� (�θ� �Լ��� �����ϰ� �ڼհ� ����
	void isEqual();

};
