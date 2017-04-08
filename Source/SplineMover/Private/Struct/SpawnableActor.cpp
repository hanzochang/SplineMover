// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineMoverPrivatePCH.h"
#include "SpawnableActor.h"

FSpawnableActor FSpawnableActor::GenerateSpawnableActor(
	ESpawnableActorPlacementType PlacementType,
	TSubclassOf<class AActor> WhatToSpawn
)
{
	FSpawnableActor SpawnableActor;
	SpawnableActor.PlacementType = PlacementType;
	SpawnableActor.WhatToSpawn = WhatToSpawn;

	return SpawnableActor;
}

FSpawnableActor FSpawnableActor::GenerateSpawnableActor(
	FString PlacementType,
	FString WhatToSpawn
)
{
	FSpawnableActor SpawnableActor;
	SpawnableActor.AssignPlacementType(PlacementType);
	SpawnableActor.AssignWhatToSpawn(WhatToSpawn);

	return SpawnableActor;
}

void FSpawnableActor::AssignPlacementType(FString Str)
{
	if (Str == "EACH_POINT")
	{
		PlacementType = ESpawnableActorPlacementType::EACH_POINT;
	}
	else
	{
		PlacementType = ESpawnableActorPlacementType::EACH_POINT;
	}

}

void FSpawnableActor::AssignWhatToSpawn(FString Str)
{
	ConstructorHelpers::FObjectFinder<UBlueprint> ActorFinder = ConstructorHelpers::FObjectFinder<UBlueprint>( *Str );
	if (ActorFinder.Succeeded())
	{
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Succeeded loading Blueprint Class")); }
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Str); }
		WhatToSpawn = (UClass*)ActorFinder.Object->GeneratedClass;

		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, WhatToSpawn->GetName()); }
	}
	else
	{
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cannot load Blueprint Class")); }
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Str); }
		static ConstructorHelpers::FObjectFinder<UBlueprint> AlternativeActorFinder( TEXT("Blueprint'/Game/BluePrint/B_DebugGrid_01.B_DebugGrid_01'") );
		if (AlternativeActorFinder.Succeeded())
		{
			WhatToSpawn = (UClass*)AlternativeActorFinder.Object->GeneratedClass;
		}

	}
}