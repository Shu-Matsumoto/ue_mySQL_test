// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHttpActor.h"

// Sets default values
AMyHttpActor::AMyHttpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AMyHttpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyHttpActor::MyHttpMethod(FString myText)
{
    // Jsonデータの作成
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField("myText", myText);

    // OutputStringにJson書き出し
    FString OutputString;
    TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

    // Httpリクエストの作成
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AMyHttpActor::OnResponseReceived);
    Request->SetURL("http://localhost:80/UE4/MySQLTest/user_registration_act.php");
    Request->SetVerb("POST");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));
    Request->SetContentAsString(OutputString);
    Request->ProcessRequest();
}

void AMyHttpActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

    // Jsonオブジェクトをデシリアライズ
    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        // Jsonから変数名myTextの値を取得
        FString str = JsonObject->GetStringField("myText");
        // UE4クライアントにデバッグメッセージを表示
        GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, str);
    }
}

