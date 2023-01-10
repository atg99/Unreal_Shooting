// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "MyBlueprintAsyncActionBase.generated.h"

/**
 * 
 */

//바인딩이벤트를 걸때 변수 갯수 2개      델리게이트 함수는 파라미터 타입 이름을 , 로 구분한다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTTDelegate, int32, Id, FString, Data, bool, Info);


UCLASS()
class SHOOTING_API UMyBlueprintAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintASSignable)  //델리게이트에서 사용하겠다? 델리게이트 사용
		FTTDelegate OnSuccess; // FTTDelegate에서 사용할 변수 선언

	UPROPERTY(BlueprintAssignable)
		FTTDelegate OnFail; 

	UPROPERTY(BlueprintAssignable)
		FTTDelegate Unknownn;

	UPROPERTY() //유프로퍼티가 없으면 가비지 컬랙터가 60초마다 삭제해서 null이 되버린다!
		int32 temp;
	UFUNCTION(BlueprintCallable, Meta = (BlueprintInternalUseOnly = "true")) //실행노드 있는 함수
		static UMyBlueprintAsyncActionBase* AsyncTest(const int ID);

	virtual void Activate() override; // override란? 자손이 부모 함수를 자기가 원하는 대로 바꿔서 쓴다 (부모 함수를 무시하고 자손걸 쓴다
	void isEqual();

};
