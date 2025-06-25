// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Actor/Enemies/Drones.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADrones::ADrones()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");


	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);

	boxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	boxCollision->SetupAttachment(RootComponent);
	boxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);

	floatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Movement");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ADrones::Explode()
{
	Destroy();
}

// Called when the game starts or when spawned
void ADrones::BeginPlay()
{
	Super::BeginPlay();
	ChooseNewLocation();
}

void ADrones::RandomMovement(float _dt)
{

	//Movement of Drones
	//Calculate distance from the targeted location, until close enough
	FVector droneLocation = GetActorLocation();
	float distance = FVector::Dist(droneLocation, currentTarget);

	if (distance <= acceptanceRadius)
	{
		ChooseNewLocation();
	}


	FVector direction = (currentTarget - droneLocation).GetSafeNormal();
	AddMovementInput(direction, (1.0f * droneSpeed) * _dt, false);
}

void ADrones::ChooseNewLocation()
{
	//Get Random Point in Map Collision Box
	if (movementBoundingBox) {
		if (movementBoundingBox->GetComponentByClass<UBoxComponent>())
		{
			currentTarget = UKismetMathLibrary::RandomPointInBoundingBox(movementBoundingBox->GetActorLocation(), movementBoundingBox->GetComponentByClass<UBoxComponent>()->GetScaledBoxExtent());
		}
	}
}

// Called every frame
void ADrones::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RandomMovement(DeltaTime);
}

