// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "MyHttpActor.generated.h"

UCLASS()
class MYSQLTEST_API AMyHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyHttpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FHttpModule* Http;

	// HTTP�ʐM�����郁�\�b�h
	UFUNCTION(BlueprintCallable, Category = "Http")
	void MyHttpMethod(FString userName, FString password);

	// HTTP�ʐM���s���ă��X�|���X���Ԃ��Ă����ۂ̃C�x���g����
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
