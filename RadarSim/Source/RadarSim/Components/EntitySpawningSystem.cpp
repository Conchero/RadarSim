// Fill out your copyright notice in the Description page of Project Settings.


#include "../Components/EntitySpawningSystem.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Actor/Enemies/EnemyEntity.h"
#include "../Actor/Enemies/Drones.h"

// Sets default values for this component's properties
UEntitySpawningSystem::UEntitySpawningSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
	// ...
}


// Called when the game starts
void UEntitySpawningSystem::BeginPlay()
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


void UEntitySpawningSystem::RemoveEntityFromPool(class AEnemyEntity* _target)
{
	if (spawnedEntities.Num() <= 0)
		return;


	spawnedEntities.RemoveAt(spawnedEntities.Find(_target));
}

// Called every frame
void UEntitySpawningSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!spawnableArea || spawnedEntities.Num() >= maxEnemyInMap)
		return;


	spawnEntityTimer += DeltaTime;

	if (spawnEntityTimer >= spawnEntityTreshold)
	{
		FVector pointInBoundingBox = UKismetMathLibrary::RandomPointInBoundingBox(GetOwner()->GetActorLocation(), spawnableArea->GetScaledBoxExtent());
		int32 randomEntity = FMath::Floor(FMath::RandRange(0, spawnableEntitiesArray.Num() - 1));
		randomEntity = randomEntity < spawnableEntitiesArray.Num() ? randomEntity : 0;
		AEnemyEntity* newEntity = GetWorld()->SpawnActor<AEnemyEntity>(spawnableEntitiesArray[randomEntity], pointInBoundingBox, FRotator::ZeroRotator);
		newEntity->OnEnemyDestroyed.AddUniqueDynamic(this, &UEntitySpawningSystem::RemoveEntityFromPool);

		if (Cast<ADrones>(newEntity))
			Cast<ADrones>(newEntity)->SetMovementBoundingBox(spawnableArea);


		spawnedEntities.Add(newEntity);

		spawnEntityTimer = 0;
	}

}

