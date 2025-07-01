// Fill out your copyright notice in the Description page of Project Settings.


#include "../Components/DroneSpawningSystem.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Actor/Enemies/Drones.h"

// Sets default values for this component's properties
UDroneSpawningSystem::UDroneSpawningSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
	// ...
}


// Called when the game starts
void UDroneSpawningSystem::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		if (GetOwner()->GetComponentByClass<UBoxComponent>())
		{
			spawnableArea = GetOwner()->GetComponentByClass<UBoxComponent>();
		}
	}

	// ...
	
}


void UDroneSpawningSystem::RemoveEntityFromPool(class ADrones* _target)
{
	if (spawnedEntities.Num() <= 0)
	return;


	spawnedEntities.RemoveAt(spawnedEntities.Find(_target));
}

// Called every frame
void UDroneSpawningSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!spawnableArea || spawnedEntities.Num() >= maxEnemyInMap)
	return;


	spawnEntityTimer += DeltaTime;

	if (spawnEntityTimer >= spawnEntityTreshold)
	{
		FVector pointInBoundingBox = UKismetMathLibrary::RandomPointInBoundingBox(GetOwner()->GetActorLocation(), spawnableArea->GetScaledBoxExtent());
		int32 randomEntity = FMath::Floor(FMath::RandRange(0,spawnableEntitiesArray.Num()-1));
		randomEntity = randomEntity < spawnableEntitiesArray.Num() ? randomEntity : 0;
		ADrones* newDrone = GetWorld()->SpawnActor<ADrones>(spawnableEntitiesArray[randomEntity], pointInBoundingBox,FRotator::ZeroRotator);
		newDrone->OnDroneDestroyed.AddUniqueDynamic(this,&UDroneSpawningSystem::RemoveEntityFromPool);
		newDrone->SetMovementBoundingBox(spawnableArea);


		spawnedEntities.Add(newDrone);

		spawnEntityTimer = 0;
	}

}

