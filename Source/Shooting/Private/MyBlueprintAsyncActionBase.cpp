// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintAsyncActionBase.h"

UMyBlueprintAsyncActionBase* UMyBlueprintAsyncActionBase::AsyncTest(const int ID)
{
	UMyBlueprintAsyncActionBase* NewAsyncTest = NewObject<UMyBlueprintAsyncActionBase>();

	NewAsyncTest->temp=ID;
	return NewAsyncTest;
}

void UMyBlueprintAsyncActionBase::Activate() {
	isEqual();
}

void UMyBlueprintAsyncActionBase :: isEqual() {

	switch (temp) {

		case 1: OnSuccess.Broadcast(temp, "succeess", true); break;
		case 2: OnFail.Broadcast(temp, "Fail", true); break;
		default: Unknownn.Broadcast(temp, "Unknown", false); break;
	}

	RemoveFromRoot();
}
