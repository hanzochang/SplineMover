// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineMoverPrivatePCH.h"
#include "SplineUnitGenerator.h"


// Sets default values for this component's properties
USplineUnitGenerator::USplineUnitGenerator()
{
}

TArray<FSplineUnit> USplineUnitGenerator::GenerateSplineUnits(FString Path)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonFullPath(Path));
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<FSplineUnit> SplineUnits;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}

		ParseJsonAndGenerateSplineUnits(SplineUnits, JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}

	return SplineUnits;
}


/*
* Private
*/

void USplineUnitGenerator::ParseJsonAndGenerateSplineUnits(TArray<FSplineUnit> &SplineUnits, TSharedPtr<FJsonObject> JsonObject)
{
	FVector PrevEndPoint = FVector{ 0,0,0 };
	TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("SplineUnits"));

	for (int32 i = 0; i < objArray.Num(); i++)
	{
		TSharedPtr<FJsonValue> value = objArray[i];
		TSharedPtr<FJsonObject> json = value->AsObject();

		ESplineUnit WaveType = ParseWaveType(json);
		FRotator UnitRotator = ParseAsRotator(json, FString("UnitRotator"));
		bool InheritRotatorPitch = json->GetBoolField(TEXT("InheritRotatorPitch"));
		bool InheritRotatorYaw = json->GetBoolField(TEXT("InheritRotatorYaw"));
		bool InheritRotatorInRoll = json->GetBoolField(TEXT("InheritRotatorInRoll"));
		float Scalar = json->GetNumberField(TEXT("Scalar"));
		int32 Density = json->GetNumberField(TEXT("Density"));
		FRotator CurveUnitRotator = ParseAsRotator(json, FString("CurveUnitRotator"));
		float CurveScalar = json->GetNumberField(TEXT("CurveScalar"));
		float WaveFreq = json->GetNumberField(TEXT("WaveFreq"));
		float Msec = json->GetNumberField(TEXT("WaveFreq"));
		int32 loop = json->GetNumberField(TEXT("loop"));
		TArray<FSpawnableActor> SpawnableActors = ParseSpawnableActors(json);

		FSplineUnit SplineUnit = FSplineUnit::GenerateSplineUnit(
			WaveType,
			UnitRotator,
			InheritRotatorPitch,
			InheritRotatorYaw,
			InheritRotatorInRoll,
			Scalar,
			Density,
			CurveUnitRotator,
			CurveScalar,
			WaveFreq,
			Msec,
			loop,
			SpawnableActors
		);

		//PrevEndPoint = SplineUnit.StartLocation + SplineUnit.Distance;
		SplineUnits.Push(SplineUnit);
	}
}

ESplineUnit USplineUnitGenerator::ParseWaveType(TSharedPtr<FJsonObject> json)
{
	FString WaveTypeStr = json->GetStringField(TEXT("WaveType"));
	ESplineUnit WaveType;

	if (WaveTypeStr == "WAVE_LINEAR")
	{
		WaveType = ESplineUnit::WAVE_LINEAR;
	}
	else if (WaveTypeStr == "WAVE_SIN")
	{
		WaveType = ESplineUnit::WAVE_SIN;
	}
	else if (WaveTypeStr == "WAVE_TRIANGLE")
	{
		WaveType = ESplineUnit::WAVE_TRIANGLE;
	}
	else
	{
		WaveType = ESplineUnit::WAVE_LINEAR;
	}

	return WaveType;
}

FVector USplineUnitGenerator::ParseAsVector(TSharedPtr<FJsonObject> json, FString KeyName)
{
	TArray<FString> ArrayJson;
	json->TryGetStringArrayField(*KeyName, ArrayJson);
	FVector Vector = FVector{ FCString::Atof(*ArrayJson[0]),
							  FCString::Atof(*ArrayJson[1]),
							  FCString::Atof(*ArrayJson[2]) };
	return Vector;
}

FRotator USplineUnitGenerator::ParseAsRotator(TSharedPtr<FJsonObject> json, FString KeyName)
{
	TArray<FString> ArrayJson;
	json->TryGetStringArrayField(*KeyName, ArrayJson);
	FRotator Rotator = FRotator{ FCString::Atof(*ArrayJson[0]),
							  FCString::Atof(*ArrayJson[1]),
							  FCString::Atof(*ArrayJson[2]) };
	return Rotator;
}

FString USplineUnitGenerator::JsonFullPath(FString Path)
{
	FString FullPath = FPaths::GameContentDir();
	FullPath += Path;
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *FullPath);

	return JsonStr;
}

TArray<FSpawnableActor> USplineUnitGenerator::ParseSpawnableActors(TSharedPtr<FJsonObject> json)
{
	TArray<FSpawnableActor> SpawnableActors;
	TArray<TSharedPtr<FJsonValue>> childArray = json->GetArrayField(TEXT("SpawnableActors"));
	if (childArray.Num() > 0)
	{
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Go")); }
		for (int32 i = 0; i < childArray.Num(); i++) {
			TSharedPtr<FJsonValue> childValue = childArray[i];
			TSharedPtr<FJsonObject> childJson = childValue->AsObject();

			FString ActorsReference = childJson->GetStringField(TEXT("ActorsReference"));
			FString PlacementType = childJson->GetStringField(TEXT("PlacementType"));

			FSpawnableActor SpawnableActor = FSpawnableActor::GenerateSpawnableActor(PlacementType, ActorsReference);
			SpawnableActors.Push(SpawnableActor);
		}
	}

	return SpawnableActors;
}
